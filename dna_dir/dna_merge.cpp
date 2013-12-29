#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <unistd.h>
#include <vector>
#include <stdint.h>
#include <sys/mman.h>
using namespace std;
const static size_t CB_LEN = 24;
const static size_t DNA_FRAME_LEN = 40;
const static size_t DNA_HEADER_LEN = 48;

struct dna_header{
    uint32_t pad1;
    uint32_t media_len;
    uint32_t pad2[10];
};

struct dna_frame{
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


vector<dna_frame> dvec;
long long p_begin_ts;
long long c_begin_ts;
string p_dnaf, c_dnaf;

int parse_option(int argc, char *argv[])
{
    int opt;
    opterr = 0;
    string usage = "Usage: ";
    usage += argv[0];
    usage += " -p prev_dnafile -c curr_dnafile -s prev_begin_ts -e curr_begin_ts";
    
    if (argc != 9)
        cout << usage << endl;

    while((opt = getopt(argc, argv, "p:c:s:e:")) != -1)
    {
        switch(opt)
        {
            case 'p':
                p_dnaf = string(optarg);
                break;
            case 'c':
                c_dnaf = string(optarg);
                break;
            case 's':
                p_begin_ts = atoll(optarg);
                break;
            case 'e':
                c_begin_ts = atoll(optarg);
                break;
            default:
                return -1;
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

int merge_dna( unsigned char *addr1, off_t pos1, unsigned char *addr2, off_t pos2)
{
    dna_control_block *cb1 = (dna_control_block *)addr1;
    dna_control_block *cb2 = (dna_control_block *)addr2;
    dna_frame *last_dna = (dna_frame *) (addr1 + pos1 - CB_LEN - DNA_FRAME_LEN);
    long long n_ts = last_dna->dna_ts - 60000;
    long long off_ts = 0;
    long p_end_ts = cb1->timestamp + last_dna->dna_ts;
    cout <<"xxx" <<  last_dna->dna_ts << endl;
    dna_header dh = *(dna_header *) (addr1 + CB_LEN);

    unsigned char *p1, *p2;
    dna_frame *d1, *d2;
    bool flag = false;
    p1 = p2 = addr1 + CB_LEN + DNA_FRAME_LEN;
    dna_control_block *cb = (dna_control_block *) p1;
    while( cb->length != 0)
    {
        p1 += CB_LEN;
        d1 = d2 = (dna_frame *) p1;
        
        while( d1 != p1 + cb->length)
        {
            if (d1->dna_ts <= n_ts)
            {
                ++d1;
                d2 = d1;
            }
            else
            {
                if (off_ts == 0)
                {
                    off_ts = cb1->timestamp - last_dna->dna_ts - d2->dna_ts;
                }
                dna_frame d = *d1;
                d.dna_ts -= off_ts;
                dvec.push_back(d);
            }
        }
        p1 += cb->length;
        cb = (dna_control_block *) p1;
    }
    
}

int main ( int argc, char *argv[] )
{
    //int ret = parse_option(argc, argv);
    int ret  =0;
    if (ret != 0)
        cout << "p_dnaf: " << p_dnaf << " c_dnaf: " << c_dnaf
            << " p_begin_ts: " << p_begin_ts << " c_begin_ts: " << c_begin_ts << endl;

    string p_dnaf = "./2.1388041199.cdna";
    string c_dnaf = "./2.1388044799.cdna";
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

    merge_dna( addr1, pos1, addr2, pos2);
    
    munmap(addr1, s1);
    fclose(fp1);
    munmap(addr2, s2);
    fclose(fp2);
    return 0;
}			/* ----------  end of function main  ---------- */
