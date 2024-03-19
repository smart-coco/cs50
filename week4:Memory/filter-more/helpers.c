#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i=0;i<height;i++)
    {
        for (int j=0;j<width;j++)
        {
            int temp=(int)round((image[i][j].rgbtBlue*1.0+image[i][j].rgbtGreen+image[i][j].rgbtRed)/3);
            image[i][j].rgbtBlue=temp;
            image[i][j].rgbtGreen=temp;
            image[i][j].rgbtRed=temp;
        }
    }
    return;
}

// Reflect image horizontally
void RGBTRIPLE_exchange(RGBTRIPLE *a,RGBTRIPLE *b)
{
    RGBTRIPLE temp=*a;
    *a=*b;
    *b=temp;
}
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i=0;i<height;i++)
    {
        for (int j=0;j<width/2;j++)
        {
            RGBTRIPLE_exchange(&image[i][j],&image[i][width-j-1]);
        }
    }
    return;
}

// Blur image
void setRGB(int type,int height,int width,int temp[height][width],RGBTRIPLE image[height][width],int i,int j)
{
    if (type==0)
    {
        image[i][j].rgbtRed=temp[i][j];
    }
    if (type==1)
    {
        image[i][j].rgbtGreen=temp[i][j];
    }
    if (type==2)
    {
        image[i][j].rgbtBlue=temp[i][j];
    }
    return;
}
int getRGB(int type,int height,int width,RGBTRIPLE image[height][width],int i,int j)
{
    if (type==0)
    {
        return image[i][j].rgbtRed*1.0;
    }
    if (type==1)
    {
        return image[i][j].rgbtGreen*1.0;
    }
    if (type==2)
    {
        return image[i][j].rgbtBlue*1.0;
    }
    return -1;
}
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int temp[height][width];

    for (int z=0;z<3;z++)
    {
        for (int i=0;i<height;i++)
            for (int j=0;j<width;j++)
            {
                //计算单像素点的均值,并赋值temp[i][j]
                int count=0;
                int sum=0;
                for (int mi=i-1;mi<=i+1;mi++)
                    for (int mj=j-1;mj<=j+1;mj++)
                    {
                        if (mi>=0 && mi<height && mj>=0 && mj<width)
                        {
                            sum+=getRGB(z,height,width,image,mi,mj);
                            count++;
                        }
                    }
                //
                temp[i][j]=round(sum*1.0/count);
            }
        //更改图片像素点值
        for (int i=0;i<height;i++)
            for (int j=0;j<width;j++)
            {
                setRGB(z,height,width,temp,image,i,j);
            }
    }
    return;
}

// Detect edges
int getERGB(int type,int height,int width,RGBTRIPLE image[height][width],int i,int j)
{
    if (i<0 || i>=height || j<0 || j>=width)
    {
        return 0;
    }
    if (type==0)
    {
        return image[i][j].rgbtRed;
    }
    if (type==1)
    {
        return image[i][j].rgbtGreen;
    }
    if (type==2)
    {
        return image[i][j].rgbtBlue;
    }
    return -1;
}
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int temp[height][width];
    int gx_compute[9]={-1,0,1,-2,0,2,-1,0,1};
    int gy_compute[9]={-1,-2,-1,0,0,0,1,2,1};

    for (int z=0;z<3;z++)
    {
        for (int i=0;i<height;i++)
            for (int j=0;j<width;j++)
            {
                //计算单像素点的Gx,Gy和最后值,并赋值temp[i][j]
                int Gx=0,Gy=0,count=0;
                for (int mi=i-1;mi<=i+1;mi++)
                    for (int mj=j-1;mj<=j+1;mj++)
                    {
                        Gx+=gx_compute[count]*getERGB(z,height,width,image,mi,mj);
                        Gy+=gy_compute[count]*getERGB(z,height,width,image,mi,mj);
                        count++;
                    }
                //
                float cmp=round(sqrt(Gx*1.0*Gx+Gy*Gy));
                temp[i][j]=cmp>255?255:cmp;
            }
        //更改图片像素点值
        for (int i=0;i<height;i++)
            for (int j=0;j<width;j++)
            {
                setRGB(z,height,width,temp,image,i,j);
            }
    }
    return;
}
