#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <sstream>
#include <string.h>
#include <unistd.h>
#include <vector>
#include <stdint.h>
#include <sys/mman.h>
using namespace std;

struct dna_header
{
    uint32_t pad1;
    uint32_t media_len;
    unsigned char pad2[40];
};

struct dna_frame
{
    uint32_t dna_ts;
    uint8_t pad[36];
};

struct dna_control_block
{
    int serial_number;
    int type;
    int length;
    int pad;
    long long timestamp;    // millisecond.
};

struct dna_buffer
{
    unsigned char *buf;
    unsigned char *buf_cur;
    unsigned char *buf_end;
    size_t byte_counter;
    size_t buflen;
};

const static size_t CB_LEN = sizeof(struct dna_control_block);
const static size_t DNA_FRAME_LEN = sizeof(struct dna_frame);
const static size_t DNA_HEADER_LEN = sizeof(struct dna_header);

vector<dna_frame> dvec;
long long p_begin_ts;
long long c_begin_ts;
int channel_id;
string p_dnaf, c_dnaf, dir;


int parse_option(int argc, char *argv[])
{
    int opt;
    opterr = 0;
    string usage = "Usage: ";
    usage += argv[0];
    usage += " -p prev_dnafile -c curr_dnafile -i channel_id -d save_dir";
    
    if (argc != 9)
        cerr<< usage << endl;

    while((opt = getopt(argc, argv, "p:c:d:i:")) != -1)
    {
        switch(opt)
        {
            case 'p':
                p_dnaf = string(optarg);
                break;
            case 'c':
                c_dnaf = string(optarg);
                break;
            case 'i':
                channel_id = atoi(optarg);
                break;
            case 'd':
                dir = string(optarg);
                break;
            default:
                break;
        }
    }
    return opterr;

}

unsigned char *map_file(FILE * fp, size_t size, size_t & mapped_size)
{
    int fd = fileno(fp);
    int page_size = sysconf(_SC_PAGE_SIZE);
    int aligned_size = (size + page_size - 1) / page_size * page_size;

    unsigned char *addr = (unsigned char *)mmap(NULL, aligned_size, PROT_READ,
                                                MAP_PRIVATE, fd, 0);
    if (addr == (unsigned char *)(-1))
    {
        return NULL;
    }
    else
    {
    }
    mapped_size = aligned_size;
    return addr;
}

int merge_dna(dna_buffer &dnabuf, unsigned char *addr1, off_t pos1, unsigned char *addr2, off_t pos2, int channel_id)
{
    FILE *dna_fp;
    dna_control_block *cb1 = (dna_control_block *)addr1;
    dna_control_block *cb2 = (dna_control_block *)addr2;
    dna_frame *last_dna = (dna_frame *) (addr1 + pos1 - CB_LEN - DNA_FRAME_LEN);
    dna_frame *clast_dna = (dna_frame *) (addr2 + pos2 - CB_LEN - DNA_FRAME_LEN);
    long long n_ts = last_dna->dna_ts - 60000;
    long long begin_ts = 0;
    long long off_ts = 0;
    long p_end_ts = cb1->timestamp + last_dna->dna_ts;
    dna_header dh = *(dna_header *) (addr1 + CB_LEN);

    unsigned char *p1, *p2;
    dna_frame *d1, *d2;
    bool flag = false;
    p1 = addr1 + CB_LEN + DNA_HEADER_LEN;
    dna_control_block *cb = (dna_control_block *) p1;
    while( cb->length != 0)
    {
        p1 += CB_LEN;
        d1 = (dna_frame *) p1;
        
        while( d1 != (dna_frame *)(p1 + cb->length))
        {
            if (d1->dna_ts <= n_ts)
            {
                ++d1;
            }
            else
            {
                if (off_ts == 0)
                {
                    dna_frame *p_d = d1 - 1;
                    //off_ts = cb1->timestamp - last_dna->dna_ts + p_d->dna_ts;
                    off_ts = p_d->dna_ts + (cb2->timestamp - cb1->timestamp - last_dna->dna_ts);
                    begin_ts = cb1->timestamp + off_ts;
                }
                dna_frame d = *d1;
                d.dna_ts -= off_ts;
                dvec.push_back(d);
                ++d1;
            }
        }
        p1 += cb->length;
        cb = (dna_control_block *) p1;
    }

    d1--;
    long long new_off = d1->dna_ts + (cb2->timestamp - cb1->timestamp -last_dna->dna_ts) - off_ts;
    dh.media_len = (new_off + clast_dna->dna_ts) / 1000;
    long long end_ts = cb2->timestamp + clast_dna->dna_ts;
    char filename[1024];
    sprintf(filename, "%s/%d.%lld.%lld.vdna", dir.c_str(), channel_id, begin_ts, end_ts);
    dna_fp = fopen(filename, "w");
    fwrite(&dh, DNA_HEADER_LEN, 1, dna_fp);
    fflush(dna_fp);
    vector<dna_frame>::const_iterator it = dvec.begin();
    while(it != dvec.end())
    {
        fwrite(&(*it), DNA_FRAME_LEN, 1, dna_fp);
        fflush(dna_fp);
        ++it;
    }
    vector<dna_frame>().swap(dvec);

    // curr dna file
   p2 = addr2 + CB_LEN + DNA_HEADER_LEN;
   cb = (dna_control_block *)p2;
   while (cb->length != 0)
   {
       p2 += CB_LEN;
       d2 = (dna_frame *)p2; 
       while( d2 != (dna_frame  *)(p2 + cb->length))
       {
           dna_frame d = *d2;
           d.dna_ts += new_off;
           if ((unsigned char*)dnabuf.buf_cur + DNA_FRAME_LEN >= dnabuf.buf_end)
           {
               fwrite(dnabuf.buf, dnabuf.buflen, 1, dna_fp);
               fflush(dna_fp);
               dnabuf.buf_cur = dnabuf.buf;
               dnabuf.buflen = 0;

           }
           memcpy(dnabuf.buf_cur, &d, DNA_FRAME_LEN);
           dnabuf.buf_cur += DNA_FRAME_LEN;
           dnabuf.buflen += DNA_FRAME_LEN;
           d2++;
       }
       p2 += cb->length;
       cb = (dna_control_block *)p2;
   }
   fwrite(dnabuf.buf, dnabuf.buflen, 1, dna_fp);
   fflush(dna_fp);
   fclose(dna_fp);
   cout << filename << endl;
   return 0;
}

int main ( int argc, char *argv[] )
{
    int ret = parse_option(argc, argv);
    if (ret != 0)
    {
        cerr<< "p_dnaf: " << p_dnaf << " c_dnaf: " << c_dnaf
            << c_begin_ts << " channel_id: " << channel_id << " dir:" <<dir << endl;;
    }

    //string p_dnaf = "./2.1388041199.cdna";
    //string c_dnaf = "./2.1388044799.cdna";
    FILE *fp1 = fopen(p_dnaf.c_str(), "r");
    if (!fp1)
    {
        cerr << "open file: " << p_dnaf << "failed" << endl;
        return -1;
    }
    ret = fseek(fp1, 0, SEEK_END);
    off_t pos1 = ftello(fp1);

    FILE *fp2 = fopen(c_dnaf.c_str(), "r");
    if (!fp2)
    {
        cerr << "open file: " << c_dnaf << "failed" << endl;
        return -1;
    }
    ret = fseek(fp2, 0, SEEK_END);
    off_t pos2 = ftello(fp2);

    size_t s1, s2;
    s1 = s2 =0;
    unsigned char* addr1 = map_file(fp1, pos1, s1);
    unsigned char* addr2 = map_file(fp2, pos2, s2);

    dna_buffer dnabuf;
    memset(&dnabuf, 0, sizeof(dna_buffer));
    size_t buflen = 8192;
    dnabuf.buf_cur = dnabuf.buf = new unsigned char[buflen];
    dnabuf.buflen = dnabuf.byte_counter = 0;
    dnabuf.buf_end = dnabuf.buf + buflen;

    merge_dna(dnabuf, addr1, pos1, addr2, pos2, channel_id);

    delete dnabuf.buf;
    dnabuf.buf = dnabuf.buf_cur = dnabuf.buf_end = NULL;
    
    munmap(addr1, s1);
    fclose(fp1);
    munmap(addr2, s2);
    fclose(fp2);
    return 0;
}			/* ----------  end of function main  ---------- */


