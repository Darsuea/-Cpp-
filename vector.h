namespace DarsueaDSA
{ 
    typedef Rank int; //定义秩
    #define DEFAULT_CAPACITY 3 //设置默认向量的容量为3

    template <typename T> class Vector //向量模板类
    {     
        protected:///内部///
            //内部字段   
            Rank _size; //向量的长度
            int _capacity; //向量的容量
            T* _elem; //向量封装的数组

            //内部方法
            void copyFrom(T const* A,Rank lo,Rank hi); //复制数组区间[lo,hi)

            void expand(); //空间不足时，进行扩容
            void shrink(); //空间过多时，进行压缩

            Rank max(Rank lo,Rank hi); //选择最大元素的下标

            bool swap(Rank lo,Rank hi); //交换算法
            void bubbleSort(Rank lo,Rank hi); //冒泡排序
            void selectionSort(Rank lo,Rank hi); //选择排序

            void merge(Rank lo,Rank hi); //归并
            void mergeSort(Rank lo,Rank hi); //归并排序

            Rank partition(Rank lo,Rank hi); //快排轴点选择
            void quickSort(Rank lo,Rank hi); //快速排序
            
            void heapSort(Rank lo,Rank hi); //堆排序
        public:///外部///
        /*构造方法*/
            //构造方法：默认无参数
            Vector()
            {
                _elem = new T[DEFAULT_CAPACITY];
                for(auto index=0 ; index <DEFAULT_CAPACITY ; ++index)
                {
                    _elem[index] = default;
                }
            }
            //构造方法：长度，容量，初始值
            Vector(int c,Rank s,T v)
            {
                _elem = new T[c];
                for(Rank index = 0;index < s;++index)
                {
                    _elem[index] = v;
                }
            }
            //构造方法：数组+数组元素个数
            Vector(T const* A,Rank n)
            {
                copyFrom(A,0,n);
            }
            //构造方法：数组+区间
            Vector(T const* A,Rank lo,Rank hi)
            {
                copyFrom(A,lo,hi);
            }
            //构造方法：向量整体复制
            Vector(Vector<T> const& V)
            {
                copyFrom(V._elem,0,V._size);
            }
            //构造方法：向量区间复制
            Vector(Vector<T> const& V,Rank lo,Rank hi)
            {
                copyFrom(V._elem,lo,hi);
            }

        /*析构方法*/
            ~Vector()
            {
                delete [] _elem;
            }

        /*只读接口*/
        Rank size() const {return _size;} //向量长度
        bool empty() const {return !_size;} //判断向量是否为空
        int disorted() const; //判断向量是否已经排好序
        Rank find(T const& e) const {return find(e,0,_size);} //无序向量整体查找
        Rank find(T const& e,Rank lo,Rank hi) const; //无序向量区间查找
        Rank search(T const& e) const {return search(e,0,_size);} //有序向量整体查找
        Rank search(T const& e,Rank lo,Rank hi) const; //有序向量区间查找

        /*可写接口*/
        T& operator[] (Rank r) const; //重载下标操作符
        T& operator= (Vector v); //重载赋值操作符，使能直接赋值
        T remove(Rank r); //删除秩为r的元素
        int remove(Rank lo,Rank hi); //删除区间[lo,hi]的所有元素，并返回删除元素的个数
        Rank insert(Rank r,T const& e); //在位置r处插入元素
        Rank insert(T const& e) {return insert(_size,e);} //默认在末尾添加元素e
        void sort(Rank lo,Rank hi); //区间[lo,hi)排序
        void sort(){sort(0,_size);} //整体排序
        void unsort(Rank lo,Rank hi); //区间[lo,hi)乱序
        void unsort() {unsort(0,_size);} //整体乱序
        void deduplicate(); //无序去重
        void uniquify(); //有序去重
        void traverse(void ( * ) (T&)); //遍历(使用函数指针，只读或部分修改)
        template <typename VSL> void traverse(VSL&); //遍历(使用函数对象，可以全局修改)
    }
}
