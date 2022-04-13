#ifndef HW_CPP_VK_MATRIX_HPP
#define HW_CPP_VK_MATRIX_HPP

#include <stdexcept>


class Matrix
{
    class ProxyRow;
public:
    // создание матрицы с нулевыми сторонами запрещено
    // по умолчанию матрица заполняется нулями
    explicit Matrix(size_t rows_num, size_t columns_num);

    // происходит создание новой динамической памяти для
    // данного объекта, старый объект продолжает владеть своей памятью
    Matrix(const Matrix & obj);
    Matrix & operator= (const Matrix & obj);

    virtual ~Matrix();

    ProxyRow & operator[] (size_t i);

    // создание нового объекта-результата
    Matrix operator+ (Matrix & obj) const;
    Matrix operator* (int32_t value) const;

    // изменение текущего объекта
    Matrix & operator+= (const Matrix & obj);
    Matrix & operator*= (int32_t value);

    bool operator== (const Matrix & obj) const;
    bool operator!= (const Matrix & obj) const;

    [[nodiscard]] size_t get_rows() const;
    [[nodiscard]] size_t get_columns() const;

    friend std::ostream & operator<< (std::ostream & stream, Matrix & obj);

private:
    [[nodiscard]] bool is_same_shape(const Matrix & obj) const;

    size_t rows_num_;
    size_t columns_num_;
    int32_t * data_;
    ProxyRow * rows_;

    class ProxyRow
    {
    public:
        ProxyRow() : proxy_row_data_(nullptr), proxy_rows_num_(0) {}
        void set(int32_t * data, size_t len)
        {
            proxy_row_data_ = data;
            proxy_rows_num_ = len;
        }

        int32_t & operator[] (size_t j)
        {
            if (j >= proxy_rows_num_)
            {
                throw std::out_of_range("Bad column index");
            }
            return proxy_row_data_[j];
        }
    private:
        int32_t * proxy_row_data_;
        size_t proxy_rows_num_;
    };
};


#endif //HW_CPP_VK_MATRIX_HPP
