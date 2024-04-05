#ifndef FCPU_H
#define FCPU_H
#include <iostream>
#include <string>
#include <map>
#include <fstream>

class FCPU {
public:
    FCPU();
    ~FCPU() = default;
    void get(std::string);
    void print();

private:
    std::map<std::string, int*> regs;
    std::map<std::string, void(FCPU::*)(std::string&, std::string&)> func; 
    std::map<std::string, int> label;
    std::map<std::string, bool> jumps;
    std::ifstream file;
    int r1 {};
    int r2 {};
    int r3 {};
    int r4 {};
    int r5 {};
    int r6 {};
    int r7 {};
    int r8 {};
    int r9 {};
    int r10 {};

private:
    void make();
    void get_labels();
    bool is_number(std::string&);
    bool check_reg(std::string&);
    void cut(std::string);
    void mov(std::string&, std::string&);
    void add(std::string&, std::string&);
    void jmp(std::string&, std::string&);
    void cmp(std::string&, std::string&);
    void sub(std::string&, std::string&);
    void div(std::string&, std::string&);
    void mul(std::string&, std::string&);
    void _and(std::string&, std::string&);
    void _or(std::string&, std::string&);
    void _xor(std::string&, std::string&);
    void _not(std::string&, std::string&);
    void jl(std::string&, std::string&);
    void je(std::string&, std::string&);
    void jle(std::string&, std::string&);
    void jg(std::string&, std::string&);
    void jge(std::string&, std::string&);
    void jne(std::string&, std::string&);
    void jz(std::string&, std::string&);
};

#endif // FCPU_H
