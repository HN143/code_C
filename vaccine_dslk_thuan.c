#include <stdio.h>
#include <stdlib.h>
#define true 1

typedef struct vaccine
{
    int soCCCD;
    char hoTen[30];
    int tuoi;
    char ngheNghiep[50];
} Vaccine;

typedef struct node
{
    Vaccine data;
    struct node *next;
} Node;

Node *first = NULL;
Node *last = NULL;

Vaccine nhapThongTin()
{
    Vaccine nguoiDk;

    printf("Nhap so CCDD: ");
    scanf("%d",&nguoiDk.soCCCD);

    printf("Nhap ho ten: ");
    fflush(stdin);
    gets(nguoiDk.hoTen);

    printf("Nhap tuoi: ");
    scanf("%d",&nguoiDk.tuoi);

    printf("Nhap nghe Nghiep: ");
    fflush(stdin);
    gets(nguoiDk.ngheNghiep);

    return nguoiDk;
}

Node *capPhatNode()
{
    Node *pNode = (Node*)malloc(sizeof(Node));
    if (pNode == NULL)
    {
        printf("Cap phat khong thanh cong");
    }
    return pNode;
}

Node *taoNode()
{
    Node *pNode = capPhatNode();
    pNode->data = nhapThongTin();
    pNode->next = NULL;
    return pNode;
}

void themNodeVaoCuoi(Node *pNode)
{
    if (first == NULL)
    {
        first = last = pNode;
    }
    else
    {
        last->next = pNode;
        pNode->next = NULL;
        last = pNode;
    }
}

void taoDanhSachNguoiDKVaccine()
{
    int stt = 1;
    while(true)
    {
        printf("\n\tNhap thong tin nguoi dang ki thu %d: \n",stt++);
        themNodeVaoCuoi(taoNode());

        printf("Nhap tiep? (Nhan y de nhap tiep): ");
        char tiep = getchar();
        if (tiep != 'y' && tiep != 'Y')
            break;
    }

}

void hienThiNguoiDk(Vaccine nguoiDk)
{
    printf("%20d%25s%10d%20s\n",nguoiDk.soCCCD,nguoiDk.hoTen,nguoiDk.tuoi,nguoiDk.ngheNghiep);
}

void hienThiDSNguoiDk()
{
    int stt = 1;

    printf("\t\t\tDANH SACH DANG KY TIEM VACCINE COVID\n");
    printf("\t%5s%20s%25s%10s%20s\n", "STT", "so CCCD", "Ho Ten", "Tuoi", "Nghe Nghiep");

    for (Node *i = first; i!=NULL; i=i->next)
    {
        printf("\t%5d",stt++);
        hienThiNguoiDk(i->data);
    }

}

Node *timNode(int soCCCD_canTim)
{
    for (Node *i = first; i!=NULL; i=i->next)
    {
        if (i->data.soCCCD == soCCCD_canTim)
            return i;
    }
    return NULL;
}

void chenPNodeSauQNode(Node *qNode)
{
    if (qNode == NULL)
    {
        printf("Khong tim thay so CCCD tren\n");
    }
    else
    {
        Node *pNode = taoNode();
        if (qNode == last)
        {
            qNode->next = pNode;
            pNode->next = NULL;
            last = pNode;
        }
        else
        {
            pNode->next = qNode->next;
            qNode->next = pNode;
        }
    }
}

void suaNode(Node *pNode)
{
    if (pNode == NULL)
        printf("Khong tim thay soCCCd tren\n");
    else
    {
        pNode->data = nhapThongTin();
    }
}

void xoaNode(Node *pNode)
{
    if (pNode == NULL)
        printf("Khong tim thay soCCCd tren\n");
    else
    {
        if (pNode == first)
        {
            first = first->next;
            free(pNode);
        }
        else if (pNode == last)
        {
            //Tìm vị trí trước last
            Node *tmp;
            for (tmp = first; tmp->next!=pNode; tmp=tmp->next);

            tmp->next = NULL;
            last = tmp;

        }
        else
        {
            //Tìm vị trí trước pNode
            Node *tmp;
            for (tmp = first; tmp->next!=pNode; tmp=tmp->next);

            tmp->next = pNode->next;
            free(pNode);
        }
    }
}

void menu()
{
    printf("\t\tMENU\n");
    printf("\t1.Tao danh sach\n");
    printf("\t2.Hien thi danh sach\n");
    printf("\t3.Chen nguoi dang ky\n");
    printf("\t4.Sua thong tin\n");
    printf("\t5.Xoa thong tin\n");
    printf("\t0.Ket thuc\n");
    printf("\tChon tu 1-4: ");
}

int main()
{
    while(true)
    {
        menu();
        int chon;
        scanf("%d",&chon);
        system("cls");

        switch(chon)
        {
        case 1:
            taoDanhSachNguoiDKVaccine();
            break;
        case 2:
            hienThiDSNguoiDk();
            break;
        case 3:
        {
            int soCCCD;
            printf("Nhap soCCCD cua nguoi can chen sau do: ");
            scanf("%d",&soCCCD);
            chenPNodeSauQNode(timNode(soCCCD));
            break;
        }
        case 5:
        {
            int soCCCD_canXoa;
            printf("Nhap soCCCD cua nguoi can Xoa: ");
            scanf("%d",&soCCCD_canXoa);
            xoaNode(timNode(soCCCD_canXoa));
            break;
        }
        case 4:
        {
            int soCCCD_canSua;
            printf("Nhap soCCCD cua nguoi can sua: ");
            scanf("%d",&soCCCD_canSua);
            suaNode(timNode(soCCCD_canSua));
            break;
        }

        case 0:
            printf("Exit!!!");
            return 0;
            break;
        default:
            printf("Chi chon tu 1-4\n");
        }
    }
}

