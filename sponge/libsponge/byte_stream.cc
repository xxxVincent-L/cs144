#include "byte_stream.hh"

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template<typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {
}

using namespace std;

ByteStream::ByteStream(const size_t capacity) : _capacity(capacity) { DUMMY_CODE(capacity); }

size_t ByteStream::write(const string &data) {
    if (remaining_capacity() == 0) {
        return 0;
    }
    size_t len = min(remaining_capacity(), data.size());
    for (size_t i = 0; i < len; i++) {
        _stream.push_back(data[i]);
    }
    _write_count += len;
    return len;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    //My version
    string output;
    size_t len_stream = _stream.size();
    if (len < len_stream) {
        for (size_t i = 0; i < len; ++i) {
            output.push_back(_stream[len_stream - len + i]);
        }
        return output;
    } else
        return string(_stream.begin(), _stream.begin() + len_stream);
    //Online version
//    size_t len2peek = min(buffer_size(), len);
//    return string().assign(_buf.begin(), _buf.begin() + len2peek);
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    DUMMY_CODE(len);
    size_t len_stream = _stream.size();
    size_t len_output = min(len, len_stream);
    for (size_t i = 0; i < len_output; i++) {
        _stream.pop_front();
    }
    // The following code and its position is very important!
    // If you put this line in `pop_output` -> success
    // If you put this line in `read` -> fail
    _read_count += len;
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
//    DUMMY_CODE(len);
    string output = peek_output(len);
    pop_output(len);

    return output;

}

void ByteStream::end_input() { _end_flag = true; }

// There is a problem that I can't change the parameter in a const func.
bool ByteStream::input_ended() const {

//    size_t len = remaining_capacity();
//    if (len == 0 && _end_flag){
//        return true;
//    }
//
//    return false;
    return _end_flag;
}

size_t ByteStream::buffer_size() const { return _stream.size(); }

bool ByteStream::buffer_empty() const {
//    if (buffer_size() == 0) {
//        return true;
//    }
//    return false;

// Above code can be directly transfer to follow one.
    return buffer_size() == 0;
}

bool ByteStream::eof() const { return _end_flag && (buffer_size() == 0); }

size_t ByteStream::bytes_written() const { return _write_count; }

size_t ByteStream::bytes_read() const { return _read_count; }

size_t ByteStream::remaining_capacity() const {
    // My codes
//    size_t len = _stream.size();
//    size_t temp_len = _capacity - len;
//    return temp_len;

    // Another version -> Clear :)
    return _capacity - _stream.size();
}
