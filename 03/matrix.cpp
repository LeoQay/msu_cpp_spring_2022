#include <iostream>
#include <stdexcept>
#include <cstring>

#include "matrix.hpp"


Matrix::Matrix(size_t rows_num, size_t columns_num)
:
rows_num_(rows_num), columns_num_(columns_num), data_(nullptr), rows_(nullptr)
{
    if (rows_num_ == 0 || columns_num_ == 0)
    {
        throw std::range_error("Number of rows or columns must be positive");
    }

    data_ = new int32_t [rows_num_ * columns_num_];
    rows_ = new ProxyRow [rows_num_];

    int32_t * setter = data_;
    for (size_t i = 0; i != rows_num_; i++)
    {
        rows_[i].set(setter, columns_num_);
        setter += columns_num_;
    }

    memset(data_, 0, (sizeof *data_) * rows_num_ * columns_num_);
}

Matrix::Matrix(const Matrix & obj)
: rows_num_(0), columns_num_(0), data_(nullptr), rows_(nullptr)
{
    *this = obj;
}

Matrix & Matrix::operator= (const Matrix & obj)
{
    if (this == &obj)
    {
        return *this;
    }

    delete [] rows_;
    delete [] data_;

    rows_num_ = obj.rows_num_;
    columns_num_ = obj.columns_num_;

    data_ = new int32_t [rows_num_ * columns_num_];
    rows_ = new ProxyRow [rows_num_];

    int32_t * setter = data_;
    for (size_t i = 0; i != rows_num_; i++)
    {
        rows_[i].set(setter, columns_num_);
        setter += columns_num_;
    }

    memcpy(data_, obj.data_, (sizeof *data_) * rows_num_ * columns_num_);

    return *this;
}

Matrix::~Matrix()
{
    delete [] rows_;
    delete [] data_;
}

Matrix::ProxyRow & Matrix::operator[] (size_t i)
{
    if (i >= rows_num_)
    {
        throw std::out_of_range("Bad row index");
    }

    return rows_[i];
}

size_t Matrix::get_rows() const
{
    return rows_num_;
}

size_t Matrix::get_columns() const
{
    return columns_num_;
}

Matrix Matrix::operator+ (Matrix & obj) const
{
    if (!is_same_shape(obj))
    {
        throw std::range_error("Different shapes");
    }

    Matrix result = *this;
    return result += obj;
}

Matrix & Matrix::operator+= (const Matrix & obj)
{
    if (!is_same_shape(obj))
    {
        throw std::range_error("Different shapes");
    }

    for (size_t i = 0; i != rows_num_ * columns_num_; i++)
    {
        data_[i] += obj.data_[i];
    }
    return *this;
}

Matrix Matrix::operator* (int32_t value) const
{
    Matrix result = *this;
    return result *= value;
}

Matrix & Matrix::operator*= (int32_t value)
{
    for (size_t i = 0; i != rows_num_ * columns_num_; i++)
    {
        data_[i] *= value;
    }
    return *this;
}

std::ostream & operator<< (std::ostream & stream, Matrix & obj)
{
    for (size_t i = 0; i != obj.rows_num_; i++)
    {
        if (obj.columns_num_ > 0)
        {
            stream << obj[i][0];
        }
        for (size_t j = 1; j != obj.columns_num_; j++)
        {
            stream << '\t' << obj[i][j];
        }
        stream << std::endl;
    }

    return stream;
}

bool Matrix::operator== (const Matrix & obj) const
{
    if (!is_same_shape(obj))
    {
        return false;
    }

    for (size_t i = 0; i != rows_num_ * columns_num_; i++)
    {
        if (data_[i] != obj.data_[i])
        {
            return false;
        }
    }
    return true;
}

bool Matrix::operator!= (const Matrix & obj) const
{
    if (!is_same_shape(obj))
    {
        return true;
    }

    for (size_t i = 0; i != rows_num_ * columns_num_; i++)
    {
        if (data_[i] != obj.data_[i])
        {
            return true;
        }
    }
    return false;
}

bool Matrix::is_same_shape(const Matrix & obj) const
{
    return rows_num_ == obj.rows_num_ && columns_num_ == obj.columns_num_;
}
