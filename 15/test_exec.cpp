#include <unistd.h>
int main() {
    execl("/tmp/xx", "", "/tmp/xx", 0);
    return 0;

}
