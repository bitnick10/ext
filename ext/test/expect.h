#ifndef EXT__EXPECT_H
#define EXT__EXPECT_H

#include <sstream>

template<typename T>
class ExpectValue {
    typedef T value_type ;
public:
    ExpectValue(ExpectValue& ev) {
		cout << "expect value construct by copy\n";
        this->file = ev.file;
        this->line = ev.line;
        this->pSpec = ev.pSpec;
        this->value = ev.value;
    }
	ExpectValue& operator=(ExpectValue& ev){
		return ExpectValue(ev);
	}
    ExpectValue(T value, Spec *pSpec, std::string file, int line) {
        cout << "expect value\n";
        this->file = file;
        this->line = line;
        this->pSpec = pSpec;
        this->value = value;
        this->pSpec->ExpectSum++;
        cout << "expect value end\n";
    }
    ~ExpectValue() {
        cout << "~ExpectValue  \n";
    }
    void ToBe(T value) {
        cout << "tobe  \n";
        if(this->value != value) {
            this->pSpec->ErrorSum++;
            std::stringstream  stream1;
            std::stringstream  stream2;
            stream1 << file << " (" << line << ")";
            stream2 << "expect " << this->value << " tobe " << value;
            pSpec->AddError(stream1.str());
            pSpec->AddError(stream2.str());
        }
    }
    void ToBeTruthy() {
        return ToBe(true);
    }
    void ToBeFalsy() {
        return ToBe(fals);
    }
private:
    std::string file;
    int line;
    Spec *pSpec;
    T value;
};

#define Expect(value)  expect(value,__FILE__,__LINE__)
template<typename T>
ExpectValue<T> expect(T value, std::string file, int line) {
    cout << "expect function\n";
    ExpectValue<T> ret(value, Spec::getInstance(), file, line) ;
    return ret;
}

#endif