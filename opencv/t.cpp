 #include <list>

#include <vector>

#include <algorithm>

//连通区域属性结构

typedef struct tagMarkRegion

{

std::list<POINT> MarkPointList;//点列表

RECT rect;

}MarkRegion;

 

//定义MarkMap 结构，用来存放等价对

typedef struct tagEqualMark

{    int MarkValue1;    //标记值

int MarkValue2;    //标记值

} EqualMark;

 

//定义MarkMapping 结构，用来存放标记映射关系

typedef struct tagMarkMapping

{    int nOriginalMark;   //第一次扫描的标记

int nMappingMark;  //等价整理之后对应标记

} MarkMapping;

 

/*

功能说明：八连通标记

参数说明：I，表示图像数据指针

           ImageWidth,表示图像宽

           ImageHeight，表示图像高

           off，表示偏移量

          nFlag,表示指定标记

           iColorType，表示颜色类型，（黑点，白点）

           markInfo，表示连通区域属性信息

返回值：连通点数量，int类型

*/

int FillAreaFlag33(LPINT I,int ImageWidth,int ImageHeight,long off,int nFlag,int iColorType,MarkRegion &markInfo)

{

     bool bNew;

     RECT rect;

     int m,n,i,j,k,nDot=1,offset,offtemp,yMin;

     int dxy[8],x,y;

     dxy[0]=-ImageWidth-1;     dxy[1]=-ImageWidth;                  dxy[2]=-ImageWidth+1;

     dxy[3]=-1;                                                                                     dxy[4]=1;

     dxy[5]=ImageWidth-1;       dxy[6]=ImageWidth;          dxy[7]=ImageWidth+1;

     rect.left=65535; rect.right=-1;

     rect.bottom=65535;   rect.top=-1;

    markInfo.MarkPointList.clear();

     POINT ptTmp;

     if(I[off]==iColorType && I[off]!=nFlag)//黑点同时未被标记的情况

     {

         I[off]=nFlag;

         x=off%ImageWidth;

         y=off/ImageWidth;

         ptTmp.x = x;

         ptTmp.y = y;

         markInfo.MarkPointList.push_back(ptTmp);

         if(x<rect.left)

              rect.left=x;

         if(x>rect.right)

              rect.right=x;

         if(y<rect.bottom)

              rect.bottom=y;

         if(y>rect.top)

              rect.top=y;

     }

     else

     {

         return 0;

     }

 

     for(i=y; i<ImageHeight; i++)

     {

         bNew=false;

         yMin=i;

         for(j=0; j<ImageWidth; j++)

         {

              offset=i*ImageWidth+j;

              if(I[offset]==nFlag)

              {

                   for(k=0; k<8; k++)//八邻域搜索

                   {

                       if(i==0 && k<=2)

                            continue;

                       if(i==ImageHeight-1 && k>=5)

                            continue;

                       if(j==0 && (k==0 || k==3 || k==5))

                            continue;

                       if(j==ImageWidth-1 && (k==2 || k==4 || k==7))

                            continue;

                       offtemp=offset+dxy[k];

                       if(I[offtemp]==iColorType && I[offtemp]!=nFlag)

                       {

                            I[offtemp]=nFlag;

                            nDot++;

                            m=offtemp/ImageWidth;

                            n=offtemp%ImageWidth;

                            ptTmp.x = n;

                            ptTmp.y = m;

                            markInfo.MarkPointList.push_back(ptTmp);

                            if(n < rect.left)

                                 rect.left=n;

                            if(n > rect.right)

                                 rect.right=n;

                            if(m < rect.bottom)

                                 rect.bottom=m;

                            if(m > rect.top)

                                 rect.top=m;

                            y=offtemp/ImageWidth;

                            if(y<=yMin)

                            {

                                 yMin=y;

                                 if(!bNew)

                                     bNew=true;

                            }

                       }

                   }

              }

         }

         if(bNew)

         {

              i=yMin-1;

         }

     }

     markInfo.rect.left = rect.left;

     markInfo.rect.right = rect.right;

     markInfo.rect.top = rect.top;

     markInfo.rect.bottom = rect.bottom;

     return nDot;

}

 

/*

功能说明：四连通标记

参数说明：I，表示图像数据指针

ImageWidth,表示图像宽

ImageHeight，表示图像高

off，表示偏移量

nFlag,表示指定标记

iColorType，表示颜色类型，（黑点，白点）

markInfo，表示连通区域属性信息

返回值：连通点数量，int类型

*/

int FillAreaFlag22(LPINT I,int ImageWidth,int ImageHeight,long off,int nFlag,int iColorType,MarkRegion &markInfo)

{

     bool bNew;

     RECT rect;

     int m,n,i,j,k,nDot=1,offset,offtemp,yMin;

     int dxy[4],x,y;

     dxy[0]=-ImageWidth;     dxy[1]=1;                

     dxy[2]=ImageWidth;      dxy[3]=-1;

     rect.left=65535; rect.right=-1;

     rect.bottom=65535;   rect.top=-1;

     markInfo.MarkPointList.clear();

     POINT ptTmp;

     if(I[off]==iColorType && I[off]!=nFlag)//黑点同时未被标记的情况

     {

         I[off]=nFlag;

         x=off%ImageWidth;

         y=off/ImageWidth;

         ptTmp.x = x;

         ptTmp.y = y;

         markInfo.MarkPointList.push_back(ptTmp);

         if(x<rect.left)

              rect.left=x;

         if(x>rect.right)

              rect.right=x;

         if(y<rect.bottom)

              rect.bottom=y;

         if(y>rect.top)

              rect.top=y;

     }

     else

     {

         return 0;

     }

 

     for(i=y; i<ImageHeight; i++)

     {

         bNew=false;

         yMin=i;

         for(j=0; j<ImageWidth; j++)

         {

              offset=i*ImageWidth+j;

              if(I[offset]==nFlag)

              {

                   for(k=0; k<4; k++)//四邻域搜索

                   {

                       if(i==0 && k==0)

                            continue;

                       if(i==ImageHeight-1 && k==2)

                            continue;

                       if(j==0 && k==3)

                            continue;

                       if(j==ImageWidth-1 && k==1)

                            continue;

                       offtemp=offset+dxy[k];

                       if(I[offtemp]==iColorType && I[offtemp]!=nFlag)

                       {

                            I[offtemp]=nFlag;

                            nDot++;

                            m=offtemp/ImageWidth;

                            n=offtemp%ImageWidth;

                            ptTmp.x = n;

                            ptTmp.y = m;

                            markInfo.MarkPointList.push_back(ptTmp);

                            if(n < rect.left)

                                 rect.left=n;

                            if(n > rect.right)

                                 rect.right=n;

                            if(m < rect.bottom)

                                 rect.bottom=m;

                            if(m > rect.top)

                                 rect.top=m;

                            y=offtemp/ImageWidth;

                            if(y<=yMin)

                            {

                                 yMin=y;

                                 if(!bNew)

                                     bNew=true;

                            }

                       }

                   }

              }

         }

         if(bNew)

         {

              i=yMin-1;

         }

     }

     markInfo.rect.left = rect.left;

     markInfo.rect.right = rect.right;

     markInfo.rect.top = rect.top;

     markInfo.rect.bottom = rect.bottom;

     return nDot;

}

 

