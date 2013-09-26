#ifndef EXT_MISC_ERROR_H
#define EXT_MISC_ERROR_H
#include <memory>
using namespace std;

class Error final {
public:
    // singleton property
    static Error * getInstance() {
        if( 0 == instance.get()) {
            instance.reset(new Error);
        }
        return instance.get();
    }
private:
    // singleton field
    friend class auto_ptr<Error>;
    static auto_ptr<Error> instance;
private:
	int unhandled_error_sum;
	string error_message;
public:
    string& GetLastError() {
        return error_message;
    }
    void SetLastError(string& errorMessage) {
        this->unhandled_error_sum = 1;
		this->error_message=errorMessage;
    }
public:
    Error()  : unhandled_error_sum(0){
        //cout << "Create Singleton" << endl;
    }
    virtual ~Error() {
        //cout << "Destroy Singleton" << endl;
    }
};

auto_ptr<Error> Error::instance;

#endif