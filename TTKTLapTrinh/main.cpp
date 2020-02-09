//
//  main.cpp
//  TTKTLapTrinh
//
//  Created by nguyen van vu on 2/2/19.
//  Copyright © 2019 nguyen van vu. All rights reserved.
//


#include <iostream>
#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <string>
#include <algorithm>    
#include <vector>
#include <stdlib.h>
#include <fstream>


#define THANG2NAMNHUAN 29
#define THANG2NAMKHONGNHUAN 28
#define THANG1 1
#define THANG3 3
#define THANG4 4
#define THANG5 5
#define THANG6 6
#define THANG7 7
#define THANG8 8
#define THANG9 9
#define THANG10 10
#define THANG11 11
#define THANG12 12
#define MAXMASINHVIEN 99999999
#define MINMASINHVIEN 00000001
#define minYear 1900
#define maxYear 2019

using namespace std;

struct Ngay_Sinh{
    int Ngay;
    int Thang;
    int Nam;
}; typedef Ngay_Sinh ns;

struct SinhVien{
    int masinhvien;
    string lop;
    string hoten;
    float DTB;
    struct Ngay_Sinh ns;
};

typedef SinhVien sv;

// functions exception cua struct sinh vien
void XoaKhoangTrangThuaDauVaCuoi(string &str);
void XoaKhoangTrangGiuaCacTu(string &str);
void InHoaKiTuDauMoiTu(string &str);
void Nhap(sv &sv);
void NhapTungSinhVien(sv a[], int n);
void ThemHoSoMoi(sv a[], int n);
void chenSinhVienMoi(sv a[] , int n );
void InDanhSach(sv a[], int n);
void VietHoa(string &str);

// FUNCTION EXCEPTION date/month/year.

bool CheckNgay( int Ngay,int Thang,int Nam);
bool CheckThang(int Thang);
bool CheckNam(int Nam);
void NhapNgayThangNam(ns &ns);
void XuatNgayThangNam(ns ns);

// FUNCTION CHANGE POSITION
void swap(sv &a,sv &b);

//ALGORITHM SORT
void selectionSortMaSinhVien(sv a[] ,int n);
void selectionSortMaLop(sv a[] ,int n);
void selectionSortNgayThang(sv a[] , int n);
void selectionSotDTB(sv a[] , int n);
void selectionSortHoTen(sv a[], int n);

void insertSortMasinhVien(sv a[],int n);
void insertSortMaLop(sv a[],int n);
void insertSortNgayThang(sv a[],int n);
void insertSortDTB(sv a[],int n);
void insertSortHoTen(sv a[],int n);

void quickSortMaSinhVien(sv a[], int left , int right);
void quickSortMaLop(sv a[], int left , int right);
void quickSortHoTen(sv a[] , int left , int right);
void quickSortNgayThang(sv a[] , int left , int right);
void quickSortDTB(sv a[] , int left , int right);

void bubbleSortMaSinhVien(sv a[] , int n);
void bubbleSortMaLop(sv a[] , int n);
void bubbleSortHoTen(sv a[] , int n);
void bubbleSortNgayThang(sv a[] , int n);
void bubbleSortDTB(sv a[] , int n);

// FUNCTION SEARCH
void linearSearchMaSinhVien(sv a[] , int k ,int n);
void linearSearchMaLop(sv a[] , int k ,int n);
void linearSearchHoTen(sv a[] , int k ,int n);
void linearSearchDTB(sv a[] , int k ,int n);

// FUNCTION DATA
void xuatDuLieu(sv a[], int n);
void XuatN(sv a[], int n);
void Xuat(sv a[], int n);

// WORK WITH NAME
vector<string> split(string str);
bool operator<(vector<string> vs1, vector<string> vs2);

// WORK WITH DATE
bool soSanhNgayThangSinh(ns *ns1, ns *ns2);

// FUNCTION STATISTIC
void thongKeSoLuongSinhVien(sv a[] , int n);
void thongKeKetQuaHocTap(sv a[] , int n);
bool checksv(sv a[] , int n);


bool CheckNgay( int Ngay,int Thang,int Nam){
    
    if ((Thang == 2) && (Ngay > 0)) {
        // kiem tra nam nhuan
        if(( Nam % 4 == 0 && Nam % 100 != 0) || Nam % 400 == 0){
            if(Ngay<=THANG2NAMNHUAN)
                return true;
        }
        else{
            if (Ngay<=THANG2NAMKHONGNHUAN) {
                return true;
            }
        }
        return false;
    }
    
    if (((Thang == THANG1)||(Thang == THANG3)||(Thang == THANG5)||(Thang == THANG7)||(Thang == THANG8)
         ||(Thang == THANG10)||(Thang == THANG12)) && (Ngay > 0) && (Ngay <= 31)) {
        return true;
    }
    
    if (((Thang==THANG4) ||(Thang==THANG6) ||(Thang==THANG9) ||(Thang==THANG11)) && ((Ngay>0) && (Ngay<=30)))
    {
        return true;
    }
    return false;
    
}

bool CheckThang(int Thang){
    // kiem tra thang nam trong 1--->12
    if(Thang >= THANG1 && Thang <= THANG12){
        return true;
    }
    else
        return false;
}

bool CheckNam(int Nam){
    
    if(Nam < minYear||Nam>maxYear)
        return false;
    return true;
}

void NhapNgayThangNam(ns &ns){
    do{
        cout<<"DD /MM /YYYY : ";
        cin>>ns.Ngay >>ns.Thang >>ns.Nam;
        
        if(!CheckNgay(ns.Ngay,ns.Thang,ns.Nam)){
            cout<<"Input date is invalid! Please re-enter!!\n";
        }
        if(!CheckThang(ns.Thang)){
            cout<<"Input month is invalid! Please re-enter!!\n";
        }
        if(!CheckNam(ns.Nam)){
            cout<<"Input year is invalid! Please re-enter!!\n";
        }
    }
    while(!CheckNgay(ns.Ngay,ns.Thang,ns.Nam)||!CheckThang(ns.Thang)||!CheckNam(ns.Nam));
    
}

//  ham xoa cac khoang trang o dau va cuoi
void XoaKhoangTrangThuaDauVaCuoi(string &str){
    while (str[0] == ' '){
        str.erase(str.begin() + 0); // xoa ki tu rong vi tri dau
    }
    while (str[str.length() - 1] == ' '){
        str.erase(str.begin() + str.length() - 1); //xoa vi tri rong cuoi chuoi
    }
}

// viet hoa tat ca cac chu
void VietHoa(string &str){
    transform(str.begin(), str.end(),str.begin(), ::toupper);
}

// xoa khoang trang o giua
void XoaKhoangTrangGiuaCacTu(string &str){
    for (int i = 0; i < str.length(); i++){
        // neu co 2 ky tu khoang trang lien tuc thi bo 1 cai
        if (str[i] == ' ' && str[i + 1] == ' '){
            str.erase(str.begin() + i);
            i--;
        }
    }
}

void InHoaKiTuDauMoiTu(string &str){
    transform(str.begin(), str.end(), str.begin(), ::tolower); // in chu thuong
    //  viet hoa ki tu dau
    if (str[0] != ' '){
        if (str[0] >= 97 && str[0] <= 122){  // 97:a , 122:z
            str[0] -= 32;//65:A
        }
    }
// i la khoang trang, i+1 khong la khoang trang thi do in hoa chu cai dau tien sau khoang trang
    for (int i = 0; i < str.length() - 1; i++){
        if (str[i] == ' ' && str[i + 1] != ' '){
            if (str[i + 1] >= 97 && str[i + 1] <= 122){
                str[i + 1] -= 32;
            }
        }
    }
}

void Nhap(sv &sv){
    do{
        printf("\nIdentifier Student: "); fflush(stdin); scanf("%d", &sv.masinhvien);
        if(sv.masinhvien < MINMASINHVIEN || sv.masinhvien > MAXMASINHVIEN ){
            cout<<"                  ---Identifier Student Invalid! Please re-enter!!----"<<endl;
            cout<<"---I dentifierStudent code consists of 8 numbers in the range of 00000001 to 99999999---"<<endl;
        }
    }
    while(sv.masinhvien < MINMASINHVIEN || sv.masinhvien > MAXMASINHVIEN);
    printf("Name student : ");cin.ignore();
    getline(cin,sv.hoten);
    XoaKhoangTrangThuaDauVaCuoi(sv.hoten);
    XoaKhoangTrangGiuaCacTu(sv.hoten);
    InHoaKiTuDauMoiTu(sv.hoten);
    printf("Identifier class: ");cin.ignore();
    getline(cin,sv.lop);
    XoaKhoangTrangThuaDauVaCuoi(sv.lop);
    VietHoa(sv.lop);
    
    NhapNgayThangNam(sv.ns);
    do{
        cout<<"Medium score(By number): ";
        cin>>sv.DTB;
        if(sv.DTB<0 || sv.DTB>10){
            cout<<"Medium score invalid !"<<endl;
            cout<<" 0 <= Medium score <= 10"<<endl;
            cout<<"Please re-enter !!"<<endl;
        }
        
    }
    while(sv.DTB<0||sv.DTB>10);
}

// Input  Sinh Vien
void NhapTungSinhVien(sv a[], int n){
    cout<<"\n____________________________________\n";
    cout<<"Fill in the student information form !!!!";
    for(int i = 0; i< n;i++){
        printf("\nEnter the Student %d:", i+1);
        Nhap(a[i]);
    }
    printf("\n____________________________________\n");
    
}

void ThemHoSoMoi(sv a[], int n){
    // them moi thong tin sinh vien
    ofstream f1;
    f1.open("DanhSachSinhVien.txt");
    cout<<"\nYou Have Selected To Enter The Student List!"<<endl;
    cout<<"\nEnter Number Of Students: "; cin>>n; f1 << n<<endl;
    NhapTungSinhVien(a, n);
    cin.ignore();
    for (int i =0; i<n; i++) {
        f1<< a[i].hoten<<endl;
        f1<< a[i].masinhvien;
        f1<< a[i].lop<<endl;
        f1<< a[i].ns.Ngay<<endl; f1<< a[i].ns.Thang<<endl; f1<< a[i].ns.Nam<<endl;
        f1<< a[i].DTB <<endl;
    }
    f1.close();
    printf("\nYou Have Successfully Entered!");
    printf("\nPress Any Key To Continue!\n");
}

void chenSinhVienMoi(sv a[] , int n ){
    int x;
    ofstream f1;
    ofstream f3;
    ifstream f2;
    f2.open("DanhSachSinhVien.txt",ios::in | ios::out);
    f3.open("DanhSachSinhVien.txt",ios::in | ios::out);
    f2 >> n; n++;
    f3 <<n;
    f1.open("DanhSachSinhVien.txt",ios::app);
    cout<<"\nYou Have Selected To Enter The Student List!"<<endl;
    cout<<"\nEnter The Location To Insert New Students : "; cin>>x;
    if (x<0) {
        cout<<" Nhap vao vi tri > 0 ";
    }
    if (x>=n) {
        x=n;
    }
    
    Nhap(a[x]);
    cin.ignore();
    f1<< a[x].hoten<<endl;
    f1<< a[x].masinhvien;
    f1<< a[x].lop<<endl;
    f1<< a[x].ns.Ngay<<endl; f1<< a[x].ns.Thang<<endl; f1<< a[x].ns.Nam<<endl;
    f1<< a[x].DTB <<endl;
    
    f1.close();
    printf("\nYou Have Successfully Entered!");
    printf("\nPress Any Key To Continue!\n");
    f2.close();
}


void xuatDuLieu(sv a[], int n){
    char ten[50];
    char lop[8];
    int i ;
    ifstream f2;
    f2.open("DanhSachSinhVien.txt");
    f2 >> n; f2.ignore();
    for ( i = 0; i<n; i++) {
        f2.getline(ten, 50);
        a[i].hoten = ten;
        f2 >> a[i].masinhvien;
        f2.getline(lop, 8);
        a[i].lop = lop;
        f2 >> a[i].ns.Ngay; f2>> a[i].ns.Thang; f2 >> a[i].ns.Nam;
        f2 >> a[i].DTB;
        f2.ignore();
    }
    f2.close();
}

// HAM XUAT TUNG THONG TIN SINH VIEN
void XuatN(sv a[], int n){
    printf("Display Students'List!\n");
    int i;
    xuatDuLieu(a, n);
    cout<<"\n+-------+---------------------------------+--------------------+-------------+------------------+--------------------+";
    cout<<"\n|  NUM  |      FIRST AND LAST NAME        | IDENTIFIER STUDENT |    CLASS    |    DD/MM/YYYY    |    MEDIUM SCORE    |";
    cout<<"\n+-------+---------------------------------+--------------------+-------------+------------------+--------------------+";
    for(i = 0;i < n;++i){
        if (i+1<10) {
            printf("\n|   %d   |", i+1);
        } else if(i+1 >= 10) {
            printf("\n|   %d  |", i+1);
        }
        cout.width(a[i].hoten.length()+1);
        cout<<a[i].hoten;
        cout.fill(' ');
        cout.width(33-a[i].hoten.length());
        cout<<"|";
        printf("      %d      |",a[i].masinhvien);
        cout.width(a[i].lop.length()+1);
        cout<<a[i].lop;
        cout.fill(' ');
        cout.width(13-a[i].lop.length());
        cout<<"|";
        printf("  %2d / %2d / %4d  |",a[i].ns.Ngay , a[i].ns.Thang , a[i].ns.Nam);
        printf("        %0.2f        |",a[i].DTB);
        cout<<"\n+-------+---------------------------------+--------------------+-------------+------------------+--------------------+";
    }
    cout<<endl;
    cout<<endl;
}


void Xuat(sv a[], int n){
    int i;
    cout<<"\n+-------+---------------------------------+--------------------+-------------+------------------+--------------------+";
    cout<<"\n|  NUM  |      FIRST AND LAST NAME        | IDENTIFIER STUDENT |    CLASS    |    DD/MM/YYYY    |    MEDIUM SCORE    |";
    cout<<"\n+-------+---------------------------------+--------------------+-------------+------------------+--------------------+";
    for(i = 0;i < n;++i){
        if (i+1<10) {
            printf("\n|   %d   |", i+1);
        } else if(i+1 >= 10) {
            printf("\n|   %d  |", i+1);
        }
        cout.width(a[i].hoten.length()+1);
        cout<<a[i].hoten;
        cout.fill(' ');
        cout.width(33-a[i].hoten.length());
        cout<<"|";
        printf("      %d      |",a[i].masinhvien);
        cout.width(a[i].lop.length()+1);
        cout<<a[i].lop;
        cout.fill(' ');
        cout.width(13-a[i].lop.length());
        cout<<"|";
        printf("  %2d / %2d / %4d  |",a[i].ns.Ngay , a[i].ns.Thang , a[i].ns.Nam);
        printf("        %0.2f        |",a[i].DTB);
        cout<<"\n+-------+---------------------------------+--------------------+-------------+------------------+--------------------+";

    }
    cout<<endl;
}
// Cac thuat toan sap xep

void swap(sv &a,sv &b){ // ham tra doi vi tri
    sv temp = a;
    a = b;
    b = temp ;
}

vector<string> split(string str)
{
    string temp;
    vector<string> result;
    
    for(char c : str)
    {
        if(c == ' ' && temp.size() > 0)
        {
            result.push_back(temp);
            temp.clear();
        }
        else
            temp.push_back(c);
    }
    
    if(temp.size() > 0)
        result.push_back(temp);
    
    return result;
}


bool operator<(vector<string> vs1, vector<string> vs2)
{ //so sanh de ghi de
    while(!vs1.empty() && !vs2.empty())
    {
        //nguyen van a
        //le thi b
        if(vs1.back() //a
           < vs2.back()) //b
            return true;
        else if(vs1.back() > vs2.back())
            return false;
        else
        {
            vs1.pop_back();
            vs2.pop_back();
        }
    }
    
    return false;
}

bool soSanhNgayThangSinh(ns *ns1, ns *ns2){
    if(ns1->Nam > ns2->Nam){
        return true;
    }
    else if(ns1->Nam == ns2->Nam){
        if(ns1->Thang > ns2->Thang){
            return true;
        }
        else if( ns1->Thang == ns2->Thang){
            if(ns1->Ngay > ns2->Ngay){
                return true;
            }
        }
    }
    return false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------Selection_Sort-----------------------------------------------------------------------
void selectionSortMaSinhVien(sv a[] ,int n){// sap xep thep ma sinh vien
    int min;
    for(int i=0;i<n-1;i++){
        min=i; // thiet lap phan tu ban dau la min
        for(int j=i+1 ; j<n ; j++){
            if(a[j].masinhvien < a[min].masinhvien) min=j;
        }
        if(min!=i){
            swap(a[i] , a[min]); // trao doi phan tu
        }
    }
}

void selectionSortDTB(sv a[] ,int n){
    int min;
    for(int i=0;i<n-1;i++){
        min=i; // thiet lap phan tu ban dau la min
        for(int j=i+1 ; j<n ; j++){
            if(a[j].DTB < a[min].DTB) min=j;
        }
        if(min!=i){
            swap(a[i], a[min]); // trao doi phan tu
        }
    }
}

void selectionSortNgayThang(sv a[] , int n){
        int min , i , j;
        for(i=0;i <n-1;i++){
            min=i; // thiet lap phan tu ban dau la min
            for( j=i+1 ; j<n ; j++){
                if(soSanhNgayThangSinh(&a[i].ns, &a[j].ns)==true){
                    swap(a[i] , a[j]);
            }
        }
    }
}

void selectionSortMaLop(sv a[] ,int n){// sap xep thep ma lop
    int min;
    for(int i=0;i<n-1;i++){
        min=i; // thiet lap phan tu ban dau la min
        for(int j=i+1 ; j<n ; j++){
            if(a[j].lop < a[min].lop) min=j;
        }
        if(min!=i){
            swap(a[i] , a[min]); // trao doi phan tu
        }
    }
}

void selectionSortHoTen(sv a[] ,int n){// sap xep thep ten sinh vien
    int min , i = 0;
    for(i=0;i < n;i++){
        min=i; // thiet lap phan tu ban dau la min
        for(int j=i+1 ; j<n ; j++){
            if(split( a[j].hoten) <split( a[min].hoten)) min=j;
        }
        if(min!=i){
            swap(a[i] , a[min]); // trao doi phan tu
        }
    }
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------insert_Sort---------------------------------------------------------------------------------


void insertSortMasinhVien(sv a[],int n){ // thep ma sinh vien
    int tg;int j;
    for(int i=1;i<n;i++){
        tg = a[i].masinhvien ;//chon 1 gia tri de chen
        j=i;// lua chon vi tri de chen
        while(j>0 && tg < a[j-1].masinhvien ){
            swap(a[j] , a[j-1]);
            j--;
        }
        if (j != i) {
            a[j].masinhvien = tg;//trao doi phan tu
        }
        
    }
}

void insertSortDTB(sv a[],int n){//theo diem trung binh
    double tg; int j;
    for(int i=1;i<n;i++){
        tg = a[i].DTB ;
        j=i;
        while(j>0 && tg < a[j-1].DTB){
            swap( a[j] , a[j-1]);
            j--;
        }
        a[j].DTB = tg;
    }
}

void insertSortNgayThang(sv a[],int n){ // theo ngay thang nam
    int j,i;
    for(i =1; i< n;i++){
        for ( j =i; j>0;j--){
            if(soSanhNgayThangSinh(&a[j-1].ns, &a[j].ns)==true){
                swap(a[j], a[j-1]);
            }
        }
    }
}

void insertSortHoTen(sv a[] , int n){// sort theo ten
    string tg ;int j;
    for(int i=1;i<n;i++){
        tg = a[i].hoten ;
        j=i;
        while(j>0 && split(tg) < split( a[j-1].hoten) ){
            swap(a[j] , a[j-1]);
            j--;
        }
        a[j].hoten = tg;
    }
}

void insertSortMaLop(sv a[],int n){ // sort theo ma lop
    string tg; int j;
    for(int i=1;i<n;i++){
        tg = a[i].lop ; j=i;
        while(j>0 && tg < a[j-1].lop){
            swap(a[j] , a[j-1]);
            j--;
        }
        a[j].lop = tg;
    }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------Quick_Sort----------------------------------------------------------------------------------

void quickSortMaSinhVien(sv a[], int left , int right)
{
    SinhVien pivot = a[right];
    int i = left;
    int j =right-1;
    while (true) {
        while (i<=j && a[i].masinhvien < pivot.masinhvien) {
            i++;
        }
        while (j>=i && a[j].masinhvien > pivot.masinhvien) {
            j--;
        }
        if(i>=j){
            break;
        }
        swap(a[i], a[j]);
        i++;
        j--;
    }
    swap(a[i],a[right]);
    if(left<j){
        quickSortMaSinhVien(a,left,i-1);
    }
    if(right>i){
        quickSortMaSinhVien(a,i+1,right);
    }
}


void quickSortMaLop(sv a[], int left , int right)
{
    SinhVien chot = a[right];
    int i = left;
    int j =right-1;
    while (true) {
        while (i<=j && a[i].lop < chot.lop) {
            i++;
        }
        while (j>=i && a[j].lop > chot.lop) {
            j--;
        }
        if(i>=j){
            break;
        }
        swap(a[i], a[j]);
        i++;
        j--;
    }
    swap(a[i],a[right]);
    if(left<j){
        quickSortMaLop(a,left,i-1);
    }
    if(right>i){
        quickSortMaLop(a,i+1,right);
    }
}

void quickSortHoTen(sv a[] , int left , int right)
{
    SinhVien pivot = a[right];
    int i = left;
    int j = right-1;
    while (true) {
        while (i<=j && split(a[i].hoten) < split(pivot.hoten)) {
            i++;
        }
        while (j>=i && split(a[j].hoten) > split(pivot.hoten)) {
            j--;
        }
        if (i>=j) {
            break;
        }
        swap(a[i], a[j]);
        i++;
        j--;
    }
    swap(a[i], a[right]);
    if (left<j) {
        quickSortHoTen(a, left, i-1);
    }
    if (right>i) {
        quickSortHoTen(a, i+1, right);
    }
}

void quickSortNgayThang(sv a[] , int left , int right){
    SinhVien pivot = a[right];
    int i = left;
    int j =right-1;
    while (true) {
        while (i<=j && soSanhNgayThangSinh(&a[i].ns, &pivot.ns) == true) {
            i++;
        }
        while (j>=i && soSanhNgayThangSinh(&pivot.ns, &a[j].ns)) {
            j--;
        }
        if(i>=j){
            break;
        }
        swap(a[i], a[j]);
        i++;
        j--;
    }
    swap(a[i],a[right]);
    if(left<j){
        quickSortNgayThang(a,left,i-1);
    }
    if(right>i){
        quickSortNgayThang(a,i+1,right);
    }
}

void quickSortDTB(sv a[], int l , int r)// theo Diem trung binh
{
    // If the first index less or equal than the last index
    if (l <= r)
    {
        // Create a Key/Pivot Element
        double key = a[(l+r)/2].DTB;
        // Create temp Variables to loop through array
        int i = l;
        int j = r;
        while (i <= j)
        {
            while (a[i].DTB < key)
                i++;
            while (a[j].DTB > key)
                j--;
            
            if (i <= j)
            {
                swap(a[i], a[j]);
                i++;
                j--;
            }
        }
        // Recursion to the smaller partition in the array after sorted above
        // Reference Giải Thuật Đệ Quy
        if (l < j)
            quickSortDTB(a, l, j);
        if (r > i)
            quickSortDTB(a, i, r);
    }
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------Bubble_Sort---------------------------------------------------------------------------------
void bubbleSortMaSinhVien(sv a[] , int n){
    int i, j;
    for(i=0;i<n;i++){
        for(j=0;j < n-1;j++){
            if(a[j].masinhvien > a[j+1].masinhvien){
                swap(a[j] , a[j+1]);
            }
        }
    }
}

void bubbleSortDTB(sv a[],int n){
    int i, j;
    for(i=0;i<n-1;i++){
        for(j=n-2;j>=i;j--){
            if(a[j].DTB > a[j+1].DTB){
                swap(a[j] , a[j+1]);
            }
        }
    }
}

void bubbleSortNgaythang(sv a[],int n){
    int i, j;
    for(i=0;i<n-1;i++){
        for(j=n-2;j>=i;j--){
            if(soSanhNgayThangSinh(&a[i].ns, &a[j].ns)==true){
                swap(a[j] , a[j+1]);
            }
        }
    }
}

void bubbleSortMaLop(sv a[],int n){
    int i, j;
    for(i=0;i<n-1;i++){
        for(j=n-2;j>=i;j--){
            if(a[j].lop > a[j+1].lop){
                swap(a[j] , a[j+1]);
            }
        }
    }
}

void bubbleSortHoTen(sv a[],int n){
    int i, j;
    for(i=0;i<n-1;i++){
        for(j=n-2;j>=i;j--){
            if(a[j].DTB > a[j+1].DTB){
                swap(a[j] , a[j+1]);
            }
        }
    }
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------Tim_Kiem_Tuyen_Tinh-------------------------------------------------------------------------

void linearSearchMaSinhVien(sv a[] , int k ,int n){
    printf("nhap vao ma sinh vien ma ban can tim : ");
    scanf("%d",&k);
    int i ;
    a[n].masinhvien = k+1;
    cout<<"\n+-------+---------------------------------+--------------------+-------------+------------------+--------------------+";
    cout<<"\n|  NUM  |      FIRST AND LAST NAME        | IDENTIFIER STUDENT |    CLASS    |    DD/MM/YYYY    |    MEDIUM SCORE    |";
    cout<<"\n+-------+---------------------------------+--------------------+-------------+------------------+--------------------+";
    for (i = 0; i< n; i++) {
        if (a[i].masinhvien == k) {
            if (i+1<10) {
                printf("\n|   %d   |", i+1);
            } else if(i+1 >= 10) {
                printf("\n|   %d  |", i+1);
            }
            cout.width(a[i].hoten.length()+1);
            cout<<a[i].hoten;
            cout.fill(' ');
            cout.width(33-a[i].hoten.length());
            cout<<"|";
            printf("      %d      |",a[i].masinhvien);
            cout.width(a[i].lop.length()+1);
            cout<<a[i].lop;
            cout.fill(' ');
            cout.width(13-a[i].lop.length());
            cout<<"|";
            printf("  %2d / %2d / %4d  |",a[i].ns.Ngay , a[i].ns.Thang , a[i].ns.Nam);
            printf("        %0.2f        |",a[i].DTB);
            cout<<"\n+-------+---------------------------------+--------------------+-------------+------------------+--------------------+";
        }
    }
    cout<<endl;
}

void linearSearchDTB(sv a[] , float h ,int n){
    printf("nhap vao khoa k: ");
    cin>>h;
    int i ;
    a[n].DTB = h+1;
    cout<<"\n+-------+---------------------------------+--------------------+-------------+------------------+--------------------+";
    cout<<"\n|  NUM  |      FIRST AND LAST NAME        | IDENTIFIER STUDENT |    CLASS    |    DD/MM/YYYY    |    MEDIUM SCORE    |";
    cout<<"\n+-------+---------------------------------+--------------------+-------------+------------------+--------------------+";
    for (i = 0; i< n; i++) {
        if (a[i].DTB == h) {
            if (i+1<10) {
                printf("\n|   %d   |", i+1);
            } else if(i+1 >= 10) {
                printf("\n|   %d  |", i+1);
            }
            cout.width(a[i].hoten.length()+1);
            cout<<a[i].hoten;
            cout.fill(' ');
            cout.width(33-a[i].hoten.length());
            cout<<"|";
            printf("      %d      |",a[i].masinhvien);
            cout.width(a[i].lop.length()+1);
            cout<<a[i].lop;
            cout.fill(' ');
            cout.width(13-a[i].lop.length());
            cout<<"|";
            printf("  %2d / %2d / %4d  |",a[i].ns.Ngay , a[i].ns.Thang , a[i].ns.Nam);
            printf("        %0.2f        |",a[i].DTB);
            cout<<"\n+-------+---------------------------------+--------------------+-------------+------------------+--------------------+";
        }
    }
    cout<<endl;
}

void linearSearchHoTenSinhVien(sv a[] , string k ,int n){
    printf("nhap vao ho ten ban can tim: ");
    cin.ignore();
    getline(cin,k);
    XoaKhoangTrangThuaDauVaCuoi(k);
    XoaKhoangTrangGiuaCacTu(k);
    InHoaKiTuDauMoiTu(k);
    int i ;
    cout<<"\n+-------+---------------------------------+--------------------+-------------+------------------+--------------------+";
    cout<<"\n|  NUM  |      FIRST AND LAST NAME        | IDENTIFIER STUDENT |    CLASS    |    DD/MM/YYYY    |    MEDIUM SCORE    |";
    cout<<"\n+-------+---------------------------------+--------------------+-------------+------------------+--------------------+";
    for (i = 0; i<n; i++) {
        if (a[i].hoten == k) {
            if (i+1<10) {
                printf("\n|   %d   |", i+1);
            } else if(i+1 >= 10) {
                printf("\n|   %d  |", i+1);
            }
            cout.width(a[i].hoten.length()+1);
            cout<<a[i].hoten;
            cout.fill(' ');
            cout.width(33-a[i].hoten.length());
            cout<<"|";
            printf("      %d      |",a[i].masinhvien);
            cout.width(a[i].lop.length()+1);
            cout<<a[i].lop;
            cout.fill(' ');
            cout.width(13-a[i].lop.length());
            cout<<"|";
            printf("  %2d / %2d / %4d  |",a[i].ns.Ngay , a[i].ns.Thang , a[i].ns.Nam);
            printf("        %0.2f        |",a[i].DTB);
            cout<<"\n+-------+---------------------------------+--------------------+-------------+------------------+--------------------+";

        }
    }
    cout<<endl;
}

void linearSearchMaLop(sv a[] , string k, int n){
    cout<<"nhap vao ma lop ban can tim : ";
    cin.ignore();
    getline(cin,k);
    XoaKhoangTrangThuaDauVaCuoi(k);
    VietHoa(k);
    int i ;
    cout<<"\n+-------+---------------------------------+--------------------+-------------+------------------+--------------------+";
    cout<<"\n|  NUM  |      FIRST AND LAST NAME        | IDENTIFIER STUDENT |    CLASS    |    DD/MM/YYYY    |    MEDIUM SCORE    |";
    cout<<"\n+-------+---------------------------------+--------------------+-------------+------------------+--------------------+";
    for (i = 0; i< n; i++) {
        if (a[i].lop.compare(k) == 0) {
            if (i+1<10) {
                printf("\n|   %d   |", i+1);
            } else if(i+1 >= 10) {
                printf("\n|   %d  |", i+1);
            }
            cout.width(a[i].hoten.length()+1);
            cout<<a[i].hoten;
            cout.fill(' ');
            cout.width(33-a[i].hoten.length());
            cout<<"|";
            printf("      %d      |",a[i].masinhvien);
            cout.width(a[i].lop.length()+1);
            cout<<a[i].lop;
            cout.fill(' ');
            cout.width(13-a[i].lop.length());
            cout<<"|";
            printf("  %2d / %2d / %4d  |",a[i].ns.Ngay , a[i].ns.Thang , a[i].ns.Nam);
            printf("        %0.2f        |",a[i].DTB);
            cout<<"\n+-------+---------------------------------+--------------------+-------------+------------------+--------------------+";
        }
    }
    printf("\n");
}


void thongKeSoLuongSinhVien(sv a[] , int n){
    int i , k=0 ,j=0 ,l=0,c =0;
    for (i=0; i<n; i++) {
        if (a[i].lop == "CNTT16") {
            c++;
        }
    }
    for (i=0; i<n; i++) {
        if (a[i].lop == "KTPM17") {
            k++;
        }
    }
    for (i=0; i<n; i++) {
        if (a[i].lop == "DTVT16") {
            j++;
        }
    }
    for (i=0; i<n; i++) {
        if (a[i].lop == "ATTT15") {
            l++;
        }
    }
     cout<<"\n+-------------+-------------+--------------+";
     cout<<"\n|   CLASS ID  |  CLASS ID   | SO SINH VIEN |";
     cout<<"\n+-------------+-------------+--------------+";
    printf("\n|    CNTT16   |   CNTT16    |      %d      |",c);
    cout<<"\n+-------------+-------------+--------------+";
    printf("\n|    KTPM17   |   KTPM17    |      %d      |",k);
    cout<<"\n+-------------+-------------+--------------+";
    printf("\n|    DTVT16   |   DTVT16    |      %d      |",j);
    cout<<"\n+-------------+-------------+--------------+";
    printf("\n|    ATTT15   |   ATTT15    |      %d      |",l);
     cout<<"\n+-------------+-------------+--------------+";
    printf("\n| TONG SO LUONG SINH VIEN   |      %d      |",n);
    cout<<"\n+------------------------------------------+"<<endl;
    
     //cout<<"Tong: "<<n<<endl;
}

void thongKeKetQuaHocTap(sv a[] , int n){
    
    int i , tongKTPM17=0 ,tongDTVT16=0 ,tongATTT15=0, tongCNTT16 =0 ,
    slxs1=0 , slg1=0 , slk1=0 , sltb1=0 , sly1=0,
    slxs2=0 , slg2=0 , slk2=0 , sltb2=0 , sly2=0,
    slxs3=0 , slg3=0 , slk3=0 , sltb3=0 , sly3=0,
    slxs4=0 , slg4=0 , slk4=0 , sltb4=0 , sly4=0,
    tongslxs=0 , tongslg=0 , tongslk=0 ,
    tongsltb=0 , tongsly=0 , TONG=0 ;
    float
    tlxs1 =0 , tlg1=0 , tlk1=0 , tltb1=0 , tly1=0 ,
    tlxs2 =0 , tlg2=0 , tlk2=0 , tltb2=0 , tly2=0 ,
    tlxs3 =0 , tlg3=0 , tlk3=0 , tltb3=0 , tly3=0 ,
    tlxs4 =0 , tlg4=0 , tlk4=0 , tltb4=0 , tly4=0 ,
    TLXS =0 , TLG =0 , TLK =0 , TLTB=0 , TLY =0 ;
    
    
    for (i=0; i<n; i++) {
        if (a[i].lop == "CNTT16") {
            tongCNTT16++;
            if (a[i].DTB >= 9) {
                slxs1++; // xuat sac
            } else if(a[i].DTB>= 8 && a[i].DTB <9 ) {
                slg1++;// gioi
            }else if (a[i].DTB <8 && a[i].DTB >= 6.5){
                slk1++;// kha
            }else if (a[i].DTB <6.5 && a[i].DTB >= 5){
                sltb1++; // trung binh
            }else{
                sly1++;// yeu
            }
        }
    }
// TINH TY LE XEP LOAI DANH HIEU SINH VIEN LOP CNTT16
    tlxs1 = ((float)slxs1 /(float)tongCNTT16)*100;
    tlg1 = ( (float)slg1/(float)tongCNTT16 )*100;
    tlk1 = ((float)slk1 /(float)tongCNTT16)*100;
    tltb1 = ((float)sltb1 /(float)tongCNTT16)*100;
    tly1 = ((float)sly1 /(float)tongCNTT16)*100;
    
    for (i=0; i<n; i++) {
        if (a[i].lop == "KTPM17") {
            tongKTPM17++;
            if (a[i].DTB >= 9) {
                slxs2++; // xuat sac
            } else if(a[i].DTB>= 8 && a[i].DTB <9 ) {
                slg2++;// gioi
            }else if (a[i].DTB <8 && a[i].DTB >= 6.5){
                slk2++;// kha
            }else if (a[i].DTB <6.5 && a[i].DTB >= 5){
                sltb2++; // trung binh
            }else{
                sly2++;// yeu
            }
        }
    }
    
    // TINH TY LE XEP LOAI DANH HIEU SINH VIEN LOP KTPM17
    tlxs2 = ((float)slxs2 /(float)tongKTPM17)*100;
    tlg2 = ((float)slg2 /(float)tongKTPM17)*100;
    tlk2 = ((float)slk2 /(float)tongKTPM17)*100;
    tltb2 = ((float)sltb2 /(float)tongKTPM17)*100;
    tly2 = ((float)sly2 /(float)tongKTPM17)*100;
    
    
    for (i=0; i<n; i++) {
        if (a[i].lop == "DTVT16") {
            tongDTVT16++;
            if (a[i].DTB >= 9) {
                slxs3++; // xuat sac
            } else if(a[i].DTB>= 8 && a[i].DTB <9 ) {
                slg3++;// gioi
            }else if (a[i].DTB <8 && a[i].DTB >= 6.5){
                slk3++;// kha
            }else if (a[i].DTB <6.5 && a[i].DTB >= 5){
                sltb3++; // trung binh
            }else{
                sly3++;// yeu
            }
        }
    }
    // TINH TY LE XEP LOAI DANH HIEU SINH VIEN LOP DTVT16
    tlxs3 = ((float)slxs3 /(float)tongDTVT16)*100;
    tlg3 = ((float)slg3 /(float)tongDTVT16)*100;
    tlk3 = ((float)slk3 /(float)tongDTVT16)*100;
    tltb3 = ((float)sltb3 /(float)tongDTVT16)*100;
    tly3 = ((float)sly3 /(float)tongDTVT16)*100;
    
    for (i=0; i<n; i++) {
        if (a[i].lop == "ATTT15") {
            tongATTT15++;
            if (a[i].DTB >= 9) {
                slxs4++; // xuat sac
            } else if(a[i].DTB>= 8 && a[i].DTB <9 ) {
                slg4++;// gioi
            }else if (a[i].DTB <8 && a[i].DTB >= 6.5){
                slk4++;// kha
            }else if (a[i].DTB <6.5 && a[i].DTB >= 5){
                sltb4++; // trung binh
            }else{
                sly4++;// yeu
            }
        }
    }
    // TINH TY LE XEP LOAI DANH HIEU SINH VIEN LOP ATTT15
    tlxs4 = ((float)slxs4 /(float)tongATTT15)*100;
    tlg4 = ((float)slg4 /(float)tongATTT15)*100;
    tlk4 = ((float)slk4 /(float)tongATTT15)*100;
    tltb4 = ((float)sltb4 /(float)tongATTT15)*100;
    tly4 = ((float)sly4 /(float)tongATTT15)*100;
    
    // TONG HOP SO LUONG TUNG DANH HIEU
    tongslxs = slxs1 + slxs2 + slxs3 + slxs4;
    tongslg = slg1 + slg2 + slg3 + slg4;
    tongslk = slk1 + slk2 + slk3 + slk4;
    tongsltb = sltb1 + sltb2 + sltb3 + sltb4;
    tongsly = sly1 + sly2 + sly3 + sly4 ;
    
    // TONG HOP TY LE TUNG DANH HIEU
    TONG = tongsly + tongsltb + tongslg + tongslxs + tongslk;
    TLXS = ((float)tongslxs / (float)TONG)*100;
    TLG = ((float)tongslg / (float)TONG)*100;
    TLK = ((float)tongslk / (float)TONG)*100;
    TLTB = ((float)tongsltb / (float)TONG)*100;
    TLY = ((float)tongsly / (float)TONG)*100;

    cout<<"\n+-------------+---------------+---------------+---------------+---------------+---------------+";
    cout<<"\n|             |   XUAT SAC    |      GIOI     |      KHA      |   TRUNG BINH  |      YEU      |";
    cout<<"\n+    MA LOP   +---------------+---------------+---------------+---------------+---------------+";
    cout<<"\n|             |   SL  |   %   |   SL  |   %   |   SL  |   %   |   SL  |   %   |   SL  |   %   |";
    cout<<"\n+-------------+---------------+---------------+---------------+---------------+---------------+";
   printf("\n|   CNTT16    |   %d   |  %.1f |   %d   |  %.1f |   %d  |  %.1f |   %d   |  %.1f  |   %d   |  %.1f |",
          slxs1 , tlxs1 , slg1 , tlg1 , slk1 , tlk1 , sltb1 , tltb1 , sly1 , tly1);
    cout<<"\n+-------------+---------------+---------------+---------------+---------------+---------------+";
   printf("\n|   KTPM17    |   %d   |  %.1f |   %d   |  %.1f |   %d   |  %.1f |   %d   |  %.1f |   %d   |  %.1f |",
          slxs2 , tlxs2 , slg2 , tlg2 , slk2 , tlk2 , sltb2 , tltb2 , sly2 , tly2);
    cout<<"\n+-------------+---------------+---------------+---------------+---------------+---------------+";
   printf("\n|   DTVT16    |   %d   |  %.1f |   %d   |  %.1f |   %d   |  %.1f |   %d   |  %.1f |   %d   |  %.1f |",
          slxs3 , tlxs3 , slg3 , tlg3 , slk3 , tlk3 , sltb3 , tltb3 , sly3 , tly3);
    cout<<"\n+-------------+---------------+---------------+---------------+---------------+---------------+";
   printf("\n|   ATTT15    |   %d   |  %.1f |   %d   |  %.1f |   %d  |  %.1f |   %d   |  %.1f  |   %d   |  %.1f  |",
          slxs4 , tlxs4 , slg4 , tlg4 , slk4 , tlk4 , sltb4 , tltb4 , sly4 , tly4);
    cout<<"\n+-------------+---------------+---------------+---------------+---------------+---------------+";
   printf("\n|   TONG      |   %d  |  %.1f |   %d  |  %.1f |   %d  |  %.1f |   %d   |  %.1f |   %d   |  %.1f |",
          tongslxs,TLXS,tongslg,TLG,tongslk,TLK,tongsltb,TLTB,tongsly,TLY);
    cout<<"\n+-------------+---------------+---------------+---------------+---------------+---------------+";
    cout<<endl;
    cout<<endl;
    cout<<endl;
}


//---------------------------------------------------------------------------------------------------------------------------------------------------------


bool checksv(sv a[] , int n){
    ifstream f3;
    f3.open("DanhSachSinhVien.txt");
    f3 >> n; f3.ignore();
    if (n!=0 && n>0) {
        return true;
    }
    else{
        return false;
    }
}


int main(int argc, const char * argv[]) {
    int n = 0,i = 0 , k = 0;
    float h = 0.0;
    string s , m;
    ifstream f2;
    f2.open("DanhSachSinhVien.txt");
    f2 >> n;
    f2.ignore();
    sv a[n] , l;
    char ten[50];
    char lop[8];
    for ( i = 0; i<n; i++) {
        f2.ignore();
        f2.getline(ten, 50);
        a[i].hoten = ten;
        f2 >> a[i].masinhvien;
        f2.getline(lop, 20);
        a[i].lop = lop ;
        f2 >> a[i].ns.Ngay; f2>> a[i].ns.Thang; f2 >> a[i].ns.Nam;
        f2 >> a[i].DTB;
        f2.ignore();
    }

    //ns b[n];
    int chon;
    int choice;
    int chon1;
    int c = 0;
    while(true){
        printf("++-----------------------------------------------------------------------------------------------------++\n");
        printf("||                                    MANAGER STUDENTS SYSTEM                                          ||\n");
        printf("++-----------------------------------------------------------------------------------------------------++\n");
        printf("||                                    1. Creat New Record                                              ||\n");
        printf("||                                    2. Display list students                                         ||\n");
        printf("||                                    3. Sort Students                                                 ||\n");
        printf("||                                    4. Search Students                                               ||\n");
        printf("||                                    5. Statistic                                                     ||\n");
        printf("||                                    6. Exit                                                          ||\n");
        printf("++-----------------------------------------------------------------------------------------------------++\n");
        printf("Enter Your Choice: ");
        scanf("%d",&chon);
        switch(chon){
            // them moi 1 sinh vien
                //checksv=true;
            case 1:
                cout<<"\n +------------------------------+";
                cout<<"\n | 1. CREAT A NEW LIST STUDENT  |";
                cout<<"\n +------------------------------+";
                cout<<"\n | 2. INSERT A NEW STUDENT      |";
                cout<<"\n +------------------------------+";
                cout<<"\nYOUR CHOICE :"; cin>>c;
                if (c==1) {
                    ThemHoSoMoi(a,n);
                } else {
                    chenSinhVienMoi(a, n);
                }
                break;
                
            // in danh sach cac sinh vien
            case 2:
                if(&checksv)
                {
                    XuatN(a, n);
                }
                break;
                //Chon thuat toan sap xep!
            case 3:
                cout<<"\n +------------------------------+";
                cout<<"\n |   CHOOSE SORT ALGORITHM!     |";
                cout<<"\n +------------------------------+";
                cout<<"\n | 1. SELECTIONSORT             |";
                cout<<"\n +------------------------------+";
                cout<<"\n | 2. INSERTSORT                |";
                cout<<"\n +------------------------------+";
                cout<<"\n | 3. QUICKSORT                 |";
                cout<<"\n +------------------------------+";
                cout<<"\n | 4. BUBBLESORT                |";
                cout<<"\n +------------------------------+"<<endl;
                cout<<"YOUR CHOICE :";scanf("%d",&chon1);
                
                 // chon theo tu khoa
                switch (chon1) {
                    case 1:
                        cout<<"Selection Sort !(Sap xep chon)"<<endl;
                        cout<<"\n +------------------------------+";
                        cout<<"\n |           KEY SORT           |";
                        cout<<"\n +------------------------------+";
                        cout<<"\n | 1. Identifier Student        |";
                        cout<<"\n +------------------------------+";
                        cout<<"\n | 2. Identifier class          |";
                        cout<<"\n +------------------------------+";
                        cout<<"\n | 3. Name Student              |";
                        cout<<"\n +------------------------------+";
                        cout<<"\n | 4. Date of Birth             |";
                        cout<<"\n +------------------------------+";
                        cout<<"\n | 5. Medium Score              |";
                        cout<<"\n +------------------------------+"<<endl;
                        cout<<"YOUR CHOICE :";cin>>choice;
                        switch (choice) {
                            case 1: // theo ma sinh vien
                                cout<<"Sort by student code!\n";
                                cout<<"After arrangement\n";
                                selectionSortMaSinhVien(a, n);
                                Xuat(a, n);
                                break;
                                
                            case 2: // theo ma lop
                                cout<<"Sort by ID Class!\n";
                                cout<<"After arrangement\n";
                                selectionSortMaLop(a, n);
                                Xuat(a, n);
                                break;
                                
                            case 3: // theo ho ten
                                cout<<"Sort by Name!\n";
                                cout<<"After arrangement\n";
                                selectionSortHoTen(a, n);
                                Xuat(a, n);
                                break;
                                
                            case 4: // theo ngay sinh
                                cout<<"Sort by Date of Birth!\n";
                                cout<<"After arrangement\n";
                                selectionSortNgayThang(a, n);
                                Xuat(a, n);
                                break;
                            
                            case 5: // theo diem trung binh
                                cout<<"Sort by medium sore!\n";
                                cout<<"After arrangement\n";
                                selectionSortDTB(a, n);
                                Xuat(a, n);
                                break;
                        }
                        break;
                        
                    case 2:
                        cout<<"InsertSort !(Sap xep chen)"<<endl;
                        cout<<"\n +------------------------------+";
                        cout<<"\n |           KEY SORT           |";
                        cout<<"\n +------------------------------+";
                        cout<<"\n | 1. Identifier Student        |";
                        cout<<"\n +------------------------------+";
                        cout<<"\n | 2. Identifier class          |";
                        cout<<"\n +------------------------------+";
                        cout<<"\n | 3. Name Student              |";
                        cout<<"\n +------------------------------+";
                        cout<<"\n | 4. Date of Birth             |";
                        cout<<"\n +------------------------------+";
                        cout<<"\n | 5. Medium Score              |";
                        cout<<"\n +------------------------------+"<<endl;
                        cout<<"YOUR CHOICE :";cin>>choice;
                        switch (choice) {
                            case 1: // theo ma sinh vien
                                cout<<"Sort by Id Student!\n";
                                cout<<"After arrangement\n";
                                insertSortMasinhVien(a, n);
                                Xuat(a, n);
                                break;
                                
                            case 2: // theo ma lop
                                cout<<"Sort by ID Class!\n";
                                cout<<"After arrangement\n";
                                insertSortMaLop(a, n);
                                Xuat(a, n);
                                break;
                                
                            case 3: // theo ma ho ten
                                cout<<"Sort by Name!\n";
                                cout<<"After arrangement\n";
                                insertSortHoTen(a, n);
                                Xuat(a, n);
                                break;
                                
                            case 4: // theo ngay sinh
                                cout<<"Sort by Date of Birth!\n";
                                cout<<"After arrangement\n";
                                insertSortNgayThang(a, n);
                                Xuat(a, n);
                                break;
                                
                            case 5: // theo diem trung binh
                                cout<<"Sort by medium sore!\n";
                                cout<<"After arrangement\n";
                                insertSortDTB(a, n);
                                Xuat(a, n);
                                break;
                        }
                        break;
                        
                    case 3:
                        cout<<"Quicksort!(Sap xep nhanh)"<<endl;
                        cout<<"\n +------------------------------+";
                        cout<<"\n |           KEY SORT           |";
                        cout<<"\n +------------------------------+";
                        cout<<"\n | 1. Identifier Student        |";
                        cout<<"\n +------------------------------+";
                        cout<<"\n | 2. Identifier class          |";
                        cout<<"\n +------------------------------+";
                        cout<<"\n | 3. Name Student              |";
                        cout<<"\n +------------------------------+";
                        cout<<"\n | 4. Date of Birth             |";
                        cout<<"\n +------------------------------+";
                        cout<<"\n | 5. Medium Score              |";
                        cout<<"\n +------------------------------+"<<endl;
                        cout<<"YOUR CHOICE :";cin>>choice;
                        switch (choice) {
                            case 1: // theo ma sv
                                cout<<"Sort by Id Student!\n";
                                cout<<"After arrangement\n";
                                quickSortMaSinhVien(a,0,n-1);
                                Xuat(a, n);
                                break;
                                
                            case 2: // theo ma lop
                                cout<<"Sort by ID Class!\n";
                                cout<<"After arrangement\n";
                                quickSortMaLop(a, 0, n-1);
                                Xuat(a, n);
                                break;
                                
                            case 3: // theo ma ho ten
                                cout<<"Sort by Name!\n";
                                cout<<"After arrangement\n";
                                selectionSortHoTen(a, n);
                                Xuat(a, n);
                                break;
                                
                            case 4: // theo ngay sinh
                                cout<<"Sort by Date of Birth!\n";
                                cout<<"After arrangement\n";
                                quickSortNgayThang(a, 0, n-1);
                                Xuat(a, n);
                                break;
                                
                            case 5: // theo diem trung binh
                                cout<<"Sort by medium sore!\n";
                                cout<<"After arrangement\n";
                                quickSortDTB(a,0,n-1);
                                Xuat(a, n);
                                break;
                        }
                        break;
                      
                    case 4:
                        cout<<"Bubblesort!(Sap xep noi bot)";
                        cout<<"\n +------------------------------+";
                        cout<<"\n |           KEY SORT           |";
                        cout<<"\n +------------------------------+";
                        cout<<"\n | 1. Identifier Student        |";
                        cout<<"\n +------------------------------+";
                        cout<<"\n | 2. Identifier class          |";
                        cout<<"\n +------------------------------+";
                        cout<<"\n | 3. Name Student              |";
                        cout<<"\n +------------------------------+";
                        cout<<"\n | 4. Date of Birth             |";
                        cout<<"\n +------------------------------+";
                        cout<<"\n | 5. Medium Score              |";
                        cout<<"\n +------------------------------+"<<endl;
                        cout<<"YOUR CHOICE :";cin>>choice;
                        switch (choice) {
                            case 1: // theo ma sinh vien
                                cout<<"Sort by Id Student!\n";
                                cout<<"After arrangement\n";
                                bubbleSortMaSinhVien(a , n);
                                Xuat(a, n);
                                break;
                                
                            case 2: // theo ma lop
                                cout<<"Sort by ID Class!\n";
                                cout<<"After arrangement\n";
                                bubbleSortMaLop(a, n);
                                Xuat(a, n);
                                break;
                                
                            case 3: // theo ma ho ten
                                cout<<"Sort by Name!\n";
                                cout<<"After arrangement\n";
                                break;
                                
                            case 4: // theo ngay sinh
                                cout<<"Sort by Date of Birth!\n";
                                cout<<"After arrangement\n";
                                bubbleSortNgaythang(a, n);
                                Xuat(a, n);
                                break;
                                
                            case 5: // theo diem trung binh
                                cout<<"Sort by medium sore!\n";
                                cout<<"After arrangement\n";
                                bubbleSortDTB(a, n);
                                Xuat(a, n);
                                break;
                        }
                        break;
                }
                break;
            case 4:
                int chon3; // chon cach tim kiem
                XuatN(a, n);
                cout<<"\n +------------------------------+";
                cout<<"\n |        LINEAR SEARCH         |";
                cout<<"\n +------------------------------+";
                cout<<"\n | 1. Identifier Student        |";
                cout<<"\n +------------------------------+";
                cout<<"\n | 2. Identifier class          |";
                cout<<"\n +------------------------------+";
                cout<<"\n | 3. Name Student              |";
                cout<<"\n +------------------------------+";
                cout<<"\n | 4. Medium Score              |";
                cout<<"\n +------------------------------+"<<endl;
                cout<<"YOUR CHOICE :";
                cin>>chon3;
                switch (chon3) {
                        case 1:
                            cout<<"Search by Identifier Student!\n";
                            linearSearchMaSinhVien(a, k, n);
                            printf("\n");
                            break;
                                
                        case 2:
                            cout<<"Search by Identifier class!\n";
                            linearSearchMaLop(a,s, n);
                            printf("\n");
                            break;
                                
                        case 3:
                            cout<<"Search by Name Student !\n";
                            linearSearchHoTenSinhVien(a, m, n);
                            printf("\n");
                            break;
                        
                        case 4:
                            cout<<"Search by medium sore!\n";
                            linearSearchDTB(a, h, n);
                            printf("\n");
                            break;
                        }
                break;
                
            case 5:
                printf("Statistic\n");
                int choice1;
                cout<<"\n +---------------------------------------------+";
                cout<<"\n |                 Statistic                   |";
                cout<<"\n +---------------------------------------------+";
                cout<<"\n | 1. Student Quantity Statistic!              |";
                cout<<"\n +---------------------------------------------+";
                cout<<"\n | 2. Statistics of Learning Results!          |";
                cout<<"\n +---------------------------------------------+"<<endl;
                cout<<"YOUR CHOICE: ";
                cin>>choice1;
                switch (choice1) {
                    case 1:
                        cout<<"Student Quantity Statistic!"<<endl;
                        thongKeSoLuongSinhVien(a, n);
                        break;
                    case 2:
                        cout<<"Statistics of Learning Results!"<<endl;
                        thongKeKetQuaHocTap(a, n);
                        break;
                    default:
                        break;
                }
                break;
            case 6:
                printf("EXIT PROGRAM !\n");
                return 0;
            break;
        }
    }
}
