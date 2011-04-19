#include<stdlib.h>
#include<stdio.h>
#include<math.h>

#include<plplot/plplot.h>


#define MAXLINE 1024
#define MAXLINES 3
#define NCOLS 100




int main(int argc,char **argv){
    FILE *fid=NULL;
    char **buffer;
    size_t *size;
    unsigned int nx,ny;   /*number of channels in x- and y-direction*/
    unsigned int i,j,k;
    double exptime;
    double expperiod;
    unsigned long binsize;
    unsigned long nelems;
    int padding=-1;
    int *data = NULL;
    unsigned int ecnt;
    int pixbuf;
    PLFLT **img_buffer;
    PLFLT zmin,zmax;
    PLINT rr[NCOLS],gg[NCOLS],bb[NCOLS];


    size = malloc(sizeof(size_t));

    buffer = malloc(sizeof(char *)*MAXLINES);
    for(i=0;i<MAXLINES;i++){
        buffer[i] = malloc(sizeof(char)*MAXLINE);
        size[i] = MAXLINE;
    }

    //fid = fopen("org_00009.cbf","rb");
    fid = fopen("LAOS3_05461.cbf","rb");
    if(fid==NULL){
        fprintf(stderr,"cannot open CBF file!\n");
        return -1;
    }
    
    i = 0;
    ecnt = 0;
    pixbuf = 0;
    while(!feof(fid)){
        if((padding>=0)){
            if(ecnt==nelems) break;
            fread(&pixbuf,sizeof(char),1,fid);
            if((((unsigned char)pixbuf)==0xd5)&&(i==0)){
                fprintf(stdout,"found start of binary stream!\n");
                data[ecnt] = 0;
                i++;
            }
            if(!i) continue;

            /*now start reading the data*/
            if(((unsigned char)pixbuf)!=0x80){
                data[ecnt] += (char)pixbuf;
                ecnt ++;
                data[ecnt] = data[ecnt-1];
                pixbuf = 0;
                continue;
            }

            fread(&pixbuf,sizeof(char)*2,1,fid);
            if(((unsigned short)pixbuf)!=0x8000){
                data[ecnt] += (short)pixbuf;
                ecnt ++;
                data[ecnt] = data[ecnt-1];
                pixbuf = 0;
                continue;
            }

            fread(&pixbuf,sizeof(char)*4,1,fid);
            data[ecnt] += pixbuf;
            ecnt++;
            data[ecnt] = data[ecnt-1];
            pixbuf = 0;



        }else{
            getline(buffer,size,fid);
            //read the ASCII header
            sscanf(buffer[0],"# Exposure_time %lf s",&exptime);
            sscanf(buffer[0],"# Exposure_period %lf s",&expperiod);
            sscanf(buffer[0],"     conversions=\"%s\"\n",buffer[1]);
            sscanf(buffer[0],"X-Binary-Size: %lu\n",&binsize);
            sscanf(buffer[0],"X-Binary-Number-of-Elements: %lu\n",&nelems);
            sscanf(buffer[0],"X-Binary-Size-Fastest-Dimension: %u\n",&ny);
            sscanf(buffer[0],"X-Binary-Size-Second-Dimension: %u\n",&nx);
            /*Remarks on dimensions:
             *According to this information 
             */
            sscanf(buffer[0],"X-Binary-Size-Padding: %u\n",&padding);
            if(padding>=0){
                fprintf(stdout,"start here with binary section\n");
                data = malloc(sizeof(int)*nx*ny);
                /*initialize data*/
                for(i=0;i<nx*ny;i++) data[i] = 0;
                
            }
        }

        
    }
    fprintf(stdout,"reached end of file ...\n\n");

    fprintf(stdout,"exposure time (sec): %lf\n",exptime);
    fprintf(stdout,"exposure period (sec): %lf\n",expperiod);
    fprintf(stdout,"compression: %s\n",buffer[1]);
    fprintf(stdout,"binary size: %lu\n",binsize);
    fprintf(stdout,"number of elements: %lu\n",nelems);
    fprintf(stdout,"framesize: %u x %u\n",nx,ny);
    fprintf(stdout,"padding: %u\n",padding);


    fclose(fid);

    //once we are done with reading the data a plot will be made
    img_buffer = malloc(sizeof(PLFLT *)*nx);
    zmin = 0; zmax = 0;
    for(i=0;i<nx;i++){
        img_buffer[i] = malloc(sizeof(PLFLT)*ny);
        for(ecnt=0;ecnt<ny;ecnt++){
            img_buffer[i][ecnt] = (PLFLT)data[i*ny+ecnt];
            if (img_buffer[i][ecnt] >= zmax) zmax = img_buffer[i][ecnt];
            if (img_buffer[i][ecnt] <= zmin) zmin = img_buffer[i][ecnt];
        }
    }
    fprintf(stdout,"z: %f %f\n",zmin,zmax);

    plsdev("xwin");
    plinit();
    plenv(0,nx,0,ny,0,0);
    pllab("channels","channels","test plot");
    plscmap1n(100);

/*
    for(i=0;i<255;i++){
        for(j=0;j<255;j++){
            for(k=0;k<255;k++){
                rr[i]=
                bb[i]=
                gg[i]=i*256/NCOLS;
            }
        }
    }*/

    //plscmap1(rr,gg,bb,NCOLS);
    plimage(img_buffer,nx,ny,0,nx,0,ny,zmin,zmax,0,nx,0,ny);

    plend();

    for(i=0;i<MAXLINES;i++){
        free(buffer[i]);
    }
    free(buffer);
    free(size);
    free(data);

    
    return 0;
}
