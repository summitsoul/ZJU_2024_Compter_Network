#include "byte_stream.hh"

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity)
    : _buffer(),  
    _bytes_written(0),
    _bytes_read(0),
    _capacity(capacity),
    _input_ended(false),
    _error(false) {}

size_t ByteStream::write(const string &data) {
    size_t bytes_to_write = std::min(data.size(), remaining_capacity());
    
    for(size_t i = 0; i < bytes_to_write; i++){
        _buffer.push_back(data[i]);
    }

    _bytes_written += bytes_to_write;
    
    return bytes_to_write;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    size_t bytes_to_peek = min(len, buffer_size());
    string output = "";

    for(size_t i = 0; i < bytes_to_peek; i++){
        output += _buffer[i];
    }

    return output;
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    size_t remove_len = std::min(len, buffer_size());

    for(size_t i = 0; i < remove_len; i++){
        _buffer.pop_front();
    }

    _bytes_read += remove_len;
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    std::string output = peek_output(len);
    
    pop_output(len);
    
    return output; 
}

void ByteStream::end_input() { _input_ended = true; }

bool ByteStream::input_ended() const { return _input_ended; }

size_t ByteStream::buffer_size() const { return _buffer.size(); }

bool ByteStream::buffer_empty() const { return _buffer.empty(); }

bool ByteStream::eof() const { return buffer_empty() && input_ended(); }

size_t ByteStream::bytes_written() const { return _bytes_written; }

size_t ByteStream::bytes_read() const { return _bytes_read; }

size_t ByteStream::remaining_capacity() const { return _capacity - _buffer.size(); }
