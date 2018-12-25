#ifndef MONTICULO_H
#define MONTICULO_H
#include "vector"
#include "algorithm"
#include "fstream"

int _izquierda(int);
int _derecha(int);
int _padre(int);
template <typename T>
void minheapFy(std::vector<T> &, int);
template <typename T>
void maxheapFy(std::vector <T> &, int);
template <typename T>
void maxheapFy(std::vector <T> &, int,int);
template <typename T>
bool esHoja(std::vector<T> &, int);
template <typename T>
void makeMinHeap(std::vector<T> &);
template <typename T>
void makeMaxHeap(std::vector<T> &);
template <typename T>
void heapSort(std::vector<T> &);
template <typename T>
void print(std::vector<T> &);
template <typename T>
void minHeapDecreaseKey(std::vector<T> &, int);
template <typename T>
void maxHeapDeceaseKey(std::vector<T> &, int);
template <typename T>
T getMin(std::vector<T> &);
template <typename T>
void deleteMin(std::vector<T> &);
template <typename T>
void insert(std::vector<T> &vec, T);

template <typename T>
void minHeapinsert(std::vector<T> &vec, T valor){
    vec.push_back(valor);
    minHeapDecreaseKey(vec, vec.size() - 1);
}

template <typename T>
void deleteMin(std::vector<T> &vec){
    std::swap(vec[0], vec[vec.size() - 1]);
    vec.pop_back();
    minheapFy(vec,0);
}

template <typename T>
T getMin(std::vector<T> &vec){
    return vec.front();
}

template <typename T>
void maxHeapDeceaseKey(std::vector<T> &vec, int index){
    if(index == 0)return;
    if(vec[index] < vec[_padre(index)])std::swap(vec[index],vec[_padre(index)]);
    maxHeapDeceaseKey(vec,_padre(index));
}

template<typename T>
void minHeapDecreaseKey(std::vector<T> &vec, int index){
    if(index == 0)return;
    if(vec[index] > vec[_padre(index)])std::swap(vec[index],vec[_padre(index)]);
    minHeapDecreaseKey(vec,_padre(index));
}

template <typename T>
void print(std::vector<T> &vec){
    std::ofstream monti("monti.dot");
    if(monti.fail()){
        std::cout<<"El archvio no se pudo abrir"<<std::endl;
        return;
    }
    monti<<"digraph{"<<std::endl;
    for(int i = 0; i < vec.size(); i++){
        if(_izquierda(i) < vec.size())monti<<vec[i]<<"->"<<vec[_izquierda(i)]<<std::endl;
        if(_derecha(i) < vec.size())monti<<vec[i]<<"->"<<vec[_derecha(i)]<<std::endl;
    }
    monti<<"}";
    monti.close();
}

template <typename T>
void heapSort(std::vector<T> &vec){
    makeMaxHeap(vec);
    auto b = vec.size();
    auto s = vec.size() - 1;
    for(int i = 0; i < b - 1; i++){
        std::swap(vec[0], vec[s]);
        s--;
        maxheapFy(vec,0,s);
    }

}

template <typename T>
void makeMaxHeap(std::vector<T> &vec){
    for(int i = vec.size() / 2; i >= 0; i--){
        maxheapFy(vec, i);
    }
}

template <typename T>
void makeMinHeap(std::vector<T> &vec){
    for(int i = vec.size() / 2; i >= 0; i--){
        minheapFy(vec,i);
    }
}


template <typename T>
bool esHoja(std::vector <T> &vec, int index){
    auto b = vec.size();
    if(_derecha(index) > b and _izquierda(index) > b)return true;
    return false;
}

int _derecha(int index){
    return 2 * index + 2;
}

int _izquierda(int index){
    return 2 * index + 1;
}

int _padre(int index){
    return (index - 1)/2;
}
template <typename T>
void minheapFy(std::vector<T> &vec, int index){
    if(esHoja(vec,index))return;
    int menor = index;
    if(vec[_izquierda(index)] < vec[menor])menor = _izquierda(index);
    if(_derecha(index) < vec.size() and vec[_derecha(index)] < vec[menor])menor = _derecha(index);
    if(menor == index)return;
    std::swap(vec[index], vec[menor]);
    minheapFy(vec, menor);

}

template <typename T>
void maxheapFy(std::vector<T> &vec, int index, int tam){
    if(_izquierda(index) > tam)return;
    if(esHoja(vec,index))return;
    int mayor = index;
    if(vec[_izquierda(index)] > vec[mayor])mayor = _izquierda(index);
    if(vec[_derecha(index)] > vec[mayor] and _derecha(index) < tam)mayor = _derecha(index);
    if(mayor == index)return;
    std::swap(vec[index], vec[mayor]);
    maxheapFy(vec, mayor,tam);
}

template <typename T>
void maxheapFy(std::vector<T> &vec, int index){
    if(esHoja(vec,index))return;
    int mayor = index;
    if(vec[_izquierda(index)] > vec[mayor])mayor = _izquierda(index);
    if(vec[_derecha(index)] > vec[mayor])mayor = _derecha(index);
    if(mayor == index)return;
    std::swap(vec[index], vec[mayor]);
    maxheapFy(vec, mayor);
}



#endif // MONTICULO_H
