#include <cstdlib>
#include <cstring>
#include <cstdio>

typedef int data_t;

class Heap
{
public:
    Heap();
    ~Heap();

    void load_data(char* file);
    void build_heap();
    void sort();
    void show();

private:
    inline int left(int index) {
        index <<= 1;
        return index;
    }

    inline int right(int index) {
        index <<= 1;
        index++;

        return index;
    }

    inline int parent(int index) {
        index >>= 1;
        return index;
    }

    void max_heap(int size, int index);
    void put_data(data_t data);
    void swap(int index1, int index2);

private:
    int m_heapsize;
    int m_maxlen;
    data_t* m_pheap;
};

Heap::Heap()
{
    m_heapsize = 0;
    m_maxlen = 16;
    m_pheap = new data_t[m_maxlen];
}

Heap::~Heap()
{
    if (m_pheap != NULL) {
        delete []m_pheap;
    }
}

void Heap::load_data(char* file)
{
    FILE* pf = fopen(file, "r");
    if (pf == NULL) {
        printf("open file error, %s\n", file);
        return;
    }

    char buff[16];
    data_t data;
    while (NULL != fgets(buff, 16, pf)) {
        int size = strlen(buff);
        if (size > 1) {
            buff[size - 1] = '\0';
            printf("load data [%s]\n", buff);
            data_t data = atoi(buff);
            put_data(data);
        }
    }
}

void Heap::build_heap()
{
    int end = m_heapsize >> 1;
    for (; end > 0; end--) {
        max_heap(m_heapsize, end);
    }
}

void Heap::sort()
{
    int size = m_heapsize;
    while (size > 1) {
        swap(size, 1);
        size--;
        max_heap(size, 1);
    }
}

void Heap::show()
{
    for (int i = 0; i <= m_heapsize; i++) {
        printf("%d ", m_pheap[i]);
    }
    printf("\n");
}

void Heap::max_heap(int size, int index)
{
    int largest = index;
    int left_place = left(index);
    int right_place = right(index);

    if (left_place <= size && m_pheap[left_place] > m_pheap[index]) {
        largest = left_place;
    }

    if (right_place <= size && m_pheap[right_place] > m_pheap[largest]) {
        largest = right_place;
    }

    if (largest != index) {
        swap(index, largest);
        max_heap(size, largest);
    }
}

void Heap::put_data(data_t data)
{
    if (m_heapsize >= m_maxlen) {
        m_maxlen *= 2;
        data_t* pdata = m_pheap;
        m_pheap = new data_t[m_maxlen];
        memcpy(m_pheap, pdata, sizeof(data_t) * (m_heapsize + 1));

        if (pdata != NULL) {
            delete []pdata;
        }
    }

    m_pheap[++m_heapsize] = data;
}

void Heap::swap(int index1, int index2)
{
    data_t tmp = m_pheap[index1];
    m_pheap[index1] = m_pheap[index2];
    m_pheap[index2] = tmp;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("usage: %s <filename>\n", argv[0]);
        return 1;
    }

    Heap heap;

    heap.load_data(argv[1]);
    heap.show();

    heap.build_heap();
    heap.show();

    heap.sort();
    heap.show();

    return 0;
}

