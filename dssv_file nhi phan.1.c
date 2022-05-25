#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
#define true 1

typedef struct
{
    char hoTen[30];
    int tuoi;
    float diemTB;
} SinhVien;

SinhVien nhapThongTinSV()
{
    SinhVien sv;

    printf("Nhap ho ten: ");
    fflush(stdin);
    gets(sv.hoTen);

    printf("Nhap tuoi: ");
    scanf("%d",&sv.tuoi);

    printf("Nhap diemTb: ");
    scanf("%f",&sv.diemTB);

    return sv;
}

int taoDSSV(SinhVien dssv[])
{
    int n;
    printf("Nhap so luong sinh vien: ");
    scanf("%d",&n);

    for (int i=0; i<n; i++)
    {
        printf("\tNhap thong tin sinh vien thu %d\n",i+1);
        dssv[i] = nhapThongTinSV();
    }
    return n;
}

void luuDssvLenFile(SinhVien dssv[], int n, char *filePath)
{
    FILE *f = fopen(filePath, "wb");
    fwrite(&dssv[0], sizeof(SinhVien),n,f);
    fclose(f);
}

int docDssvTuFile(SinhVien dssv[], char *filePath)
{
    int n = 0;
    FILE *f = fopen(filePath,"rb");
    while(true)
    {
        if(fread(&dssv[n++], sizeof(SinhVien),1,f)<=0)
            break;
    }
    fclose(f);
    return n-1;
}

void hienThiSinhVien(SinhVien sv)
{
    printf("%25s%10d%10.2f\n",sv.hoTen, sv.tuoi, sv.diemTB);
}

void hienThiDssv(SinhVien dssv[], int n)
{
    printf("\t\t\tDANH SACH SINH VIEN\n");
    printf("\t%5s%25s%10s%10s\n", "STT", "Ho ten", "Tuoi", "Diem Tb");
    for (int i=0; i<n; i++)
    {
        printf("\t%5d",i+1);
        hienThiSinhVien(dssv[i]);
    }
}

void themSvVaoCuoifile(SinhVien sv, char *filePath)
{
    FILE *f = fopen(filePath, "ab");
    sv = nhapThongTinSV();
    fwrite(&sv,sizeof(SinhVien),1,f);
    fclose(f);
}

int timChiSoSvTheoTen(SinhVien dssv[], int n, char *tenCanTim)
{
    for (int i=0; i<n; i++)
    {
        if (strcmp(dssv[i].hoTen,tenCanTim) == 0)
            return i;
    }
    return -1;
}

void suaThongTinSV(SinhVien dssv[], int n, char *tenCanTim, char *filePath)
{
    int index = timChiSoSvTheoTen(dssv,n,tenCanTim);
    if (index < 0)
        printf("Khong tim thay sinh vien %s\n",tenCanTim);
    else
    {
        dssv[index] = nhapThongTinSV();
    }
    luuDssvLenFile(dssv,n,filePath);
}

void menu()
{
    printf("\t\tMENU\n");
    printf("\t1.Tao danh sach sinh vien\n");
    printf("\t2.Hien thong tin sinh vien\n");
    printf("\t3.Bo sung sinh vien vao cuoi file\n");
    printf("\t4.Sua thong tin sinh vien\n");
    printf("\t0.Exit!!!\n");
    printf("\tChon tu 0-3: ");
}
int main()
{
    SinhVien dssv[MAX], sv;
    int n;

    while(true)
    {
        menu();
        int chon;
        scanf("%d",&chon);
        system("cls");

        switch(chon)
        {
            case 1:
            {
                n = taoDSSV(dssv);
                luuDssvLenFile(dssv,n,"dSach.c");
                break;
            }
            case 2:
            {
                n = docDssvTuFile(dssv,"dSach.c");
                hienThiDssv(dssv,n);
                break;
            }
            case 3:
            {
                themSvVaoCuoifile(sv,"dSach.c");
                hienThiDssv(dssv,n);
                break;
            }
            case 4:
            {
                char tenCanSua[30];
                printf("Nhap ho ten sv can sua: ");
                fflush(stdin);
                gets(tenCanSua);
                suaThongTinSV(dssv,n,tenCanSua,"dSach.c");
                hienThiDssv(dssv,n);
                break;
            }
            case 0:
            {
                printf("\tEXIT!!!");
                return 0;
                break;
            }

            default:
                printf("Chi chon tu 0-4: ");

        }
//        printf("Nhan phim bat ki de quay ve menu \n");
//        getchar();
//        system("cls");
    }

}
