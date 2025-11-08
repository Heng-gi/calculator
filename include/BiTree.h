#ifndef BITREE_H
#define BITREE_H

#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <iomanip>
using namespace std;

#define MAX_TREE_SIZE 100
#define OK 1
#define ERROR 0

typedef int Status;

template <typename TElemType>
class BiTNode{
public:
    TElemType data;
    BiTNode *lchild;
    BiTNode *rchild;

    BiTNode(const TElemType &val):data(val),lchild(nullptr),rchild(nullptr){}
    BiTNode(const TElemType &val,BiTNode* lchild, BiTNode* rchild):data(val),lchild(lchild),rchild(rchild){}
};

template <typename TElemType>
class BiTree{
private:
    BiTNode<TElemType> *root;

    //辅助函数：递归释放结点
    void destroy(BiTNode<TElemType> *node){
        if(!node) return;
        destroy(node->lchild);
        destroy(node->rchild);
        delete node;
    }

    int GetDepth(BiTNode<TElemType> *root)const{
        if(!root){
            return 0;
        }
        return 1+std::max(GetDepth(root->lchild),GetDepth(root->rchild));
    }

public:
    //构造空二叉树
    BiTree():root(nullptr){}

    BiTNode<TElemType>* GetRoot(){
        return root;
    }

    void setRoot(BiTNode<TElemType>* node){
        root = node;
    }
    
    //在空树中创建根结点
    void CreateRoot(const TElemType& val){
        root=new BiTNode<TElemType>(val);
    }

    //在空树中创建带左右子树的根结点
    void CreateNode(const TElemType &val,BiTNode<TElemType> *lchild, BiTNode<TElemType> *rchild){
        root=new BiTNode<TElemType>(val,lchild,rchild);
    }

    int TreeDepth(){
        return GetDepth(root);
    }

    void LevelTraverse() {
        if (!root) return;
        int depth = TreeDepth();
        int cellWidth = 4; // 每个节点的最小打印宽度
        queue<BiTNode<TElemType>*> q;
        q.push(root);

        for (int level = 0; level < depth; ++level) {
            int count = q.size();
            int frontSpaces = (pow(2, depth - level - 1) - 1) * (cellWidth / 2);
            int betweenSpaces = (pow(2, depth - level) - 1) * (cellWidth / 2);
            cout << string(frontSpaces, ' ');

            for (int i = 0; i < count; ++i) {
                BiTNode<TElemType>* node = q.front();
                q.pop();
                if (node) {
                    cout << setw(2) << node->data;
                    q.push(node->lchild);
                    q.push(node->rchild);
                } else {
                    cout << "  ";
                    q.push(nullptr);
                    q.push(nullptr);
                }
                if (i != count - 1) cout << string(betweenSpaces, ' ');
            }
            cout << "\n";
        }
    }

    ~BiTree(){
        destroy(root);
    }
};

#endif