#ifndef MATRIX_H
#define MATRIX_H

#include "sqlist.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;

class Matrix{
public:
    vector<vector<double>> a;
    int rows,cols;

    Matrix():rows(0), cols(0){}
    Matrix(int r, int c, double val=0):rows(r),cols(c),a(r,vector<double> (c,val)){}
    Matrix(const vector<vector<double>> &data):a(data),rows(a.size()),cols(a[0].size()){}

    void print() const{
        for(auto row:a){
            for(auto val:row){
                cout<<val<<"\t";
            }
            cout<<endl;
        }
    }

    Matrix operator+(const Matrix &B) const{
        if(rows!=B.rows || cols!=B.cols)
            throw invalid_argument("Matrix dimension mismatch");
        Matrix C(rows,cols);
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                C.a[i][j]=a[i][j]+B.a[i][j];
            }
        }
        return C;
    }

    Matrix operator-(const Matrix &B) const{
        if(rows!=B.rows || cols!=B.cols)
            throw invalid_argument("Matrix dimension mismatch");
        Matrix C(rows,cols);
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                C.a[i][j]=a[i][j]-B.a[i][j];
            }
        }
        return C;
    }

    Matrix operator*(const Matrix &B) const{
        if(cols!=B.rows)
            throw invalid_argument("Matrix dimension mismatch");
        Matrix C(rows,B.cols);
        for(int i=0;i<rows;i++){
            for(int j=0;j<B.cols;j++){
                for(int k=0;k<cols;k++){
                    C.a[i][j]+=a[i][k]*B.a[k][j];
                }
            }
        }
        return C;
    }

    Matrix transpose() const{
        Matrix B(cols,rows);
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                B.a[j][i]=a[i][j];
            }
        }
        return B;
    }

    void swap(int i, int j) {
        if(i<0 || i>=rows || j<0 ||j>=rows)
            throw invalid_argument("argument overflow");
        vector<double> tmp=a[i];
        a[i]=a[j];
        a[j]=tmp;
    }

    Matrix inverse() const{
        if(rows!=cols)
            throw invalid_argument("matrix dimension mismatch");
        Matrix B(rows,cols*2);
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++)
                B.a[i][j]=a[i][j];
            for(int j=0;j<cols;j++)
                B.a[i][cols + j] = (i == j ? 1.0 : 0.0);
        }
        for(int j=0;j<rows;j++){
            int pivot=j;
            for(int i=j;i<rows;i++){
                if(fabs(B.a[i][j])>fabs(B.a[pivot][j])){
                    pivot=i;
                }
            }
            if(fabs(B.a[pivot][j])<1e-9)
                throw invalid_argument("matrix irreversibility");
            B.swap(j,pivot);
            double diag=B.a[j][j];
            for(int k=j;k<B.cols;k++){
                B.a[j][k]/=diag;
            }
            for(int k=0;k<rows;k++){
                if(k==j) continue;
                double factor=B.a[k][j];
                for(int p=j;p<B.cols;p++){
                    B.a[k][p]-=factor*B.a[j][p];
                }
            }
        }
        Matrix C(rows,cols);
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                C.a[i][j]=B.a[i][cols+j];
            }
        }
        return C;
    }

    double determinant() const{
        if(rows!=cols)
            throw  invalid_argument("matrix dimension dismatch");
        Matrix B(a);
        double det=1;
        for(int j=0;j<rows;j++){
            int pivot=j;
            for(int i=j;i<rows;i++){
                if(fabs(B.a[i][j])>fabs(B.a[pivot][j])){
                    pivot=i;
                }
            }
            if(fabs(B.a[pivot][j])<1e-6)
                return 0;
            if(j!=pivot){
                B.swap(j,pivot);
                det*=-1;
            }
            double diag=B.a[j][j];
            for(int k=j;k<B.cols;k++){
                B.a[j][k]/=diag;
            }
            det*=diag;
            for(int k=0;k<rows;k++){
                if(k==j) continue;
                double factor=B.a[k][j];
                for(int p=j;p<B.cols;p++){
                    B.a[k][p]-=factor*B.a[j][p];
                }
            }
        }
        return det;
    }

    pair<Matrix,Matrix> GramSchmidtQR() const{
        Matrix Q(rows,cols);
        Matrix R(cols,cols);
        for(int j=0;j<cols;j++){
            vector<double> u(rows);
            for(int i=0;i<rows;i++)
                u[i]=a[i][j];
            for(int i=0;i<j;i++){
                R.a[i][j]=0;
                for(int k=0;k<rows;k++){
                    R.a[i][j]+=Q.a[k][i]*a[k][j];
                }
                for(int k=0;k<rows;k++){
                    u[k]-=R.a[i][j]*Q.a[k][i];
                }
            }
            R.a[j][j]=0;
            for(int k=0;k<rows;k++){
                R.a[j][j]+=u[k]*u[k];
            }
            R.a[j][j]=sqrt(R.a[j][j]);
            for(int k=0;k<rows;k++){
                Q.a[k][j]=u[k]/R.a[j][j];
            }
        }
        return {Q, R};
    }

    vector<double> eig(int max_iter=1000, double e=1e-9) const{
        if(rows!=cols)
            throw invalid_argument("Matrix dimension dismatch");
        Matrix A(a);
        for(int k=0;k<max_iter;k++){
            auto [Q,R]=A.GramSchmidtQR();
            Matrix Anew(R*Q);
            double diff=0;
            for(int j=0;j<rows;j++){
                diff+=fabs(A.a[j][j]-Anew.a[j][j]);
            }
            if(diff<e)
                break;
            A=Anew;
        }
        vector<double> eig;
        for(int i=0;i<rows;i++){
            if(eig.empty()){
                eig.push_back(A.a[i][i]);
                continue;
            }
            int flag=1;
            for(double val:eig){
                if(fabs(val-A.a[i][i])<1e-6){
                    flag=0;
                    break;
                }
            }
            if(flag){
                eig.push_back(A.a[i][i]);
            }
        }
        return eig;
    }
};

#endif