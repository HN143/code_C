#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define true 1
#define false 0

typedef struct
{
    char hoTen[30];
    int namSinh;
    float diemTB;
} SinhVien;

SinhVien *capPhatSinhvien()
{
    return (SinhVien*)malloc(sizeof(SinhVien));
}

SinhVien *capPhatDanhSachSinhVien(int n)
{
    return (SinhVien*)malloc(sizeof(SinhVien)*n);
}

SinhVien *capPhatKhiThem1SV(SinhVien *ds, int *n)
{
    if (*n ==0 || ds ==NULL)
    {
        *n=1;
        return capPhatSinhvien();
    }
    else
    {
        (*n)++;
        ds = realloc(ds,(*n)*sizeof(SinhVien));
        return ds;
    }
}

SinhVien *capPhatKhiXoa1SV(SinhVien *ds, int *n)
{
    if (*n ==0 || ds ==NULL)
    {
        *n = 0;
        return NULL;
    }
    else
    {
        (*n)--;
        ds = realloc(ds,(*n)*sizeof(SinhVien));
        return ds;
    }
}

SinhVien nhapSV()
{
    SinhVien sv;
    printf("\tHo ten: ");
    fflush(stdin);
    gets(sv.hoTen);

    printf("\tNam sinh: ");
    scanf("%d",&sv.namSinh);

    printf("\tDiem TB: ");
    scanf("%f",&sv.diemTB);

    return sv;
}
SinhVien *taoDanhSachKhiBietTruocSoSV(int n)
{
    SinhVien *ds = capPhatDanhSachSinhVien(n);
    for (int i=0; i<n; i++)
    {
        printf("\t\tNhap thong tin sinh vien thu %d\n",i+1);
        ds[i] = nhapSV();
    }
    return ds;
}

SinhVien *taoDanhSachKhiChuaBietTruocSoSV(int *n)
{
    SinhVien *ds = NULL;
    int stt =1;
    while (true)
    {
        printf("\t\tNhap thong tin sinh vien thu %d\n",stt++);
        ds = capPhatKhiThem1SV(ds,n);
        ds[(*n)-1] = nhapSV();

        char tiep;
        printf("Nhap y de tiep tuc: ");
        fflush(stdin);
        tiep = getchar();
        if (tiep != 'y' || tiep != 'Y' )
            break;
    }
    return ds;
}
void hienThiSinhVien(SinhVien sv)
{
    printf("%25s%10d%10.2f\n",sv.hoTen, sv.namSinh, sv.diemTB);
}
void hienThiDanhSach(SinhVien *ds, int n)
{
    printf("\t\t\tDSSV\n");
    printf("%5s%25s%10s%10s\n", "STT", "HO TEN", "NAM SINH", "DIEM TB");
    for (int i=0; i<n; i++)
    {
        printf("%5d",i+1);
        hienThiSinhVien(ds[i]);
    }
}

int timChiSoSinhVien(SinhVien *ds, int n, char *hoTenCanTim)
{
    for (int i=0; i<n; i++)
    {
        if (strcmp(ds[i].hoTen,hoTenCanTim) == 0)
            return i;
    }
    return -1;
}

SinhVien *themSinhVienSauTen(SinhVien *ds,int *n, char *hoTenCanTim)
{
    int index = timChiSoSinhVien(ds,*n,hoTenCanTim);
    if (index == -1)
    {
        printf("\tKhong tim duoc sinh vien %s\n",hoTenCanTim);

    }
    else
    {
        ds = capPhatKhiThem1SV(ds,n);
        for (int i=(*n)-1; i>index +1; i--)
        {
            ds[i] = ds[i-1];
        }
        ds[index +1] = nhapSV();
    }
    return ds;

}

void suaSinhVienTheoTen(SinhVien *ds, int n, char *hoTenCanSua)
{
    int index = timChiSoSinhVien(ds,n,hoTenCanSua);
    if (index == -1)
    {
        printf("\tKhong tim duoc sinh vien %s\n",hoTenCanSua);
    }
    else
    {
        ds[index] = nhapSV();
    }
}

SinhVien *xoaSinhVienTheoTen(SinhVien *ds,int *n, char *hoTenCanXoa)
{
    int index = timChiSoSinhVien(ds,*n,hoTenCanXoa);
    if (index == -1)
    {
        printf("\tKhong tim duoc sinh vien %s\n",hoTenCanXoa);
    }
    else
    {
        ds = capPhatKhiXoa1SV(ds,n);
        for (int i=index; i<(*n)-1; i++)
        {
            ds[i] = ds[i+1];
        }

    }
    return ds;

}

void menu()
{
    printf("\t\t\tMENU\n");
    printf("\t1. Tao danh sach sinh vien\n");
    printf("\t2. Hien thi danh sach sinh vien\n");
    printf("\t3. Them sinh vien sau ten\n");
    printf("\t4. Sua sinh vien theo ten\n");
    printf("\t5. Xoa sinh vien theo ten\n");
    printf("\t0. Exit\n");
    printf("\t\tVui long chon: ");
}


int main()
{
    SinhVien *ds = NULL;
    int n=0;

    while (true)
    {
        menu();

        int chon;
        scanf("%d",&chon);
        system("cls");
        switch(chon)
        {
            case 1:
                printf("\tBan da chon tao danh sach sinh vien\n");
                ds = taoDanhSachKhiChuaBietTruocSoSV(&n);
                printf("\tBan da tao thanh cong danh sach\n");
                break;
            case 2:
                hienThiDanhSach(ds,n);
                system("pause");
                break;
            case 3:
                printf("\tBan da chon them sinh vien sau ten\n");
                printf("\tNhap ho ten sinh vien truoc (da co): ");

                char hoTen[30];
                fflush(stdin);
                gets(hoTen);

                ds = themSinhVienSauTen(ds,&n,hoTen);

                break;
            case 4:
                printf("\tBan da chon sua sinh vien theo ten\n");
                printf("\tNhap ho ten can sua: ");
                char hoTen1[30];
                fflush(stdin);
                gets(hoTen1);

                suaSinhVienTheoTen(ds,n,hoTen1);

                break;
            case 5:
                printf("\tBan da chon xoa sinh vien sau ten\n");
                printf("\tNhap ho ten sinh vien truoc (da co): ");

                char hoTen2[30];
                fflush(stdin);
                gets(hoTen2);

                ds = xoaSinhVienTheoTen(ds,&n,hoTen2);

                break;
            case 0:
                printf("\tEXIT!!!");
                return 0;
                break;
            default:
                printf("\tVui long chon 0-5: \n");
                break;
        }
        printf("\tNhan phim bat ki de tro ve MENU: ");
        getchar();
        system("cls");
    }


}

