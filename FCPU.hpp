#include "FCPU.h"

FCPU::FCPU() {
    make();
}

void FCPU::get(std::string name) {
    std::string line;
    get_labels();
    this->file.open("assm_code.txt");
    if (file.is_open()) {
        while (std::getline(file, line)) {
            this->cut(line);
        }
    } else {
        std::cout << "File is not open !!!" << std::endl;
    }
    file.close();
}

void FCPU::get_labels() {
    std::string line;
    this->file.open("assm_code.txt");
    if (this->file.is_open()) {
        while (!(this->file.eof())) {
            std::getline(this->file, line);
            if (line.find(':') != -1) {
                line.erase(line.begin() + line.find(':'));
                this->label[line] = this->file.tellg();
            }
        } 
    }
    this->file.close();
}

void FCPU::cut(std::string rhs) {
    std::string oper = "";
    std::string reg = "";
    std::string src = "";
    if (rhs.find(':') != -1) {
        return;
    }
    if (rhs.find(',') != -1) {
        rhs.erase(rhs.begin() + rhs.find(','));
    }
    int space = 0;
    for (int i = 0; i < rhs.size(); ++i) {
        if (rhs[i] == ' ') {
            ++space;
        }
    }
    if (space == 1) {
        for (int i = 0; i < rhs.size(); ++i) {
            if (rhs[i] == ' ') {
                oper += rhs.substr(0, i);
                rhs.erase(rhs.begin(), rhs.begin() + i + 1);
            }
        }
        reg += rhs;
    }
    if (2 == space) {
        for (int i = 0; i < rhs.size(); ++i) {
            if (rhs[i] == ' ') {
                oper += rhs.substr(0, i);
                rhs.erase(rhs.begin(), rhs.begin() + i + 1);
                reg += rhs.substr(0, rhs.find(' '));
                rhs.erase(rhs.begin(), rhs.begin() + rhs.find(' ') + 1);
            }
        }
        src += rhs;
    }
    (this->*func[oper])(reg, src);
}

void FCPU::make() {
    regs["r1"] = &r1;
    regs["r2"] = &r2;
    regs["r3"] = &r3;
    regs["r4"] = &r4;
    regs["r5"] = &r5;
    regs["r6"] = &r6;
    regs["r7"] = &r7;
    regs["r8"] = &r8;
    regs["r9"] = &r9;
    regs["r10"] = &r10;
    
    jumps["je"] = false;
    jumps["jne"] = false;
    jumps["jl"] = false;
    jumps["jle"] = false;
    jumps["jg"] = false;
    jumps["jge"] = false;
    jumps["jz"] = false;
    jumps["jnz"] = false;

    func["mov"] = &FCPU::mov;
    func["add"] = &FCPU::add;
    func["cmp"] = &FCPU::cmp; 
    func["sub"] = &FCPU::sub;
    func["div"] = &FCPU::div;
    func["mul"] = &FCPU::mul;
    func["and"] = &FCPU::_and;
    func["or"] = &FCPU::_or;
    func["xor"] = &FCPU::_xor;
    func["not"] = &FCPU::_not;
    func["jmp"] = &FCPU::jmp;
    func["jz"] = &FCPU::jz;
    func["jg"] = &FCPU::jg;
    func["jge"] = &FCPU::jge;
    func["jl"] = &FCPU::jl;
    func["jle"] = &FCPU::jle;
    func["jne"] = &FCPU::jne;
}

bool FCPU::check_reg(std::string& src) {
    for (int i = 0; i < regs.size(); ++i) {
        if ((regs.find(src)) == (regs.end())) {
            return false;
        }
    }
    return true;
}

bool FCPU::is_number(std::string& src) {
    bool flag = true;
    for (int i = 0; i < src.length(); ++i) {
        if (src[i] >= '0' && src[i] <= '9') {
            flag = true;
        } else {
            flag = false;
            break;
        }
    }
    return flag;
}

void FCPU::mov(std::string& dest, std::string& src) {
    if (check_reg(dest)) {
        if (is_number(src)) {
            *(regs[dest]) = stoi(src);
        }
        if (check_reg(src)) {
            *(regs[dest]) = *(regs[src]);
        }
    } else {
        throw std::runtime_error("register is not found");
    }
    // std::cout << "r1" << " " << r1 << std::endl;
    //std::cout << "r2" << " " << r2 << std::endl;
}

void FCPU::add(std::string& dest, std::string& src) {
    if (check_reg(dest)) {
        if (is_number(src)) {
            *(regs[dest]) += stoi(src);
        }
        if (check_reg(src)) {
            *(regs[dest]) += *(regs[src]);
        }
    } else {
        throw std::runtime_error("register is not found");
    }
    // std::cout << "r1" << " " << r1 << std::endl;
    //std::cout << "r2" << " " << r2 << std::endl;

}

void FCPU::sub(std::string& dest, std::string& src) {
    if (check_reg(dest)) {
        if (is_number(src)) {
            *(regs[dest]) -= stoi(src);
        }
        if (check_reg(src)) {
            *(regs[dest]) -= *(regs[src]);
        }
    } else {
        throw std::runtime_error("register is not found");
    }
    // std::cout << "r1" << " " << r1 << std::endl;
    // std::cout << "r2" << " " << r2 << std::endl;
}

void FCPU::div(std::string& dest, std::string& src) {
    if (check_reg(dest)) {
        if (is_number(src)) {
            *(regs[dest]) /= stoi(src);
        }
        if (check_reg(src)) {
            *(regs[dest]) /= *(regs[src]);
        }
    } else {
        throw std::runtime_error("register is not found");
    }
}

void FCPU::mul(std::string& dest, std::string& src) {
    if (check_reg(dest)) {
        if (is_number(src)) {
            *(regs[dest]) *= stoi(src);
        }
        if (check_reg(src)) {
            *(regs[dest]) *= *(regs[src]);
        }
    } else {
        throw std::runtime_error("register is not found");
    }
}

void FCPU::_and(std::string& dest, std::string& src) {
    if (check_reg(dest)) {
        if (is_number(src)) {
            *(regs[dest]) &= stoi(src);
        }
        if (check_reg(src)) {
            *(regs[dest]) &= *(regs[src]);
        }
    } else {
        throw std::runtime_error("register is not found");
    }
    // std::cout << "r1" << " " << r1 << std::endl;
    // std::cout << "r2" << " " << r2 << std::endl;
}

void FCPU::_or(std::string& dest, std::string& src) {
    if (check_reg(dest)) {
        if (is_number(src)) {
            *(regs[dest]) |= stoi(src);
        }
        if (check_reg(src)) {
            *(regs[dest]) |= *(regs[src]);
        }
    } else {
        throw std::runtime_error("register is not found");
    }
    // std::cout << "r1" << " " << r1 << std::endl;
    // std::cout << "r2" << " " << r2 << std::endl;
}

void FCPU::_xor(std::string& dest, std::string& src) {
    if (check_reg(dest)) {
        if (is_number(src)) {
            *(regs[dest]) ^= stoi(src);
        }
        if (check_reg(src)) {
            *(regs[dest]) ^= *(regs[src]);
        }
    } else {
        throw std::runtime_error("register is not found");
    }
    // std::cout << "r1" << " " << r1 << std::endl;
    // std::cout << "r2" << " " << r2 << std::endl;
}

void FCPU::_not(std::string& dest, std::string& src) {
    if (check_reg(dest)) {
            *(regs[dest]) = ~(stoi(dest));
    } else {
        throw std::runtime_error("register is not found");
    }
}

void FCPU::cmp(std::string& dest, std::string& src) {
    if (check_reg(dest)) {
        if (is_number(src) && src != "0") {
            if (*(regs[dest]) == (stoi(src))) {
                jumps["je"] = true;
                jumps["jne"] = false;
                jumps["jl"] = false;
                jumps["jle"] = true;
                jumps["jg"] = false;
                jumps["jge"] = true;
                jumps["jz"] = false;
                return;
            }
            else if (*(regs[dest]) < (stoi(src))) {
                jumps["je"] = false;
                jumps["jne"] = true;
                jumps["jl"] = true;
                jumps["jle"] = true;
                jumps["jg"] = false;
                jumps["jge"] = false;
                jumps["jz"] = false;
                return;
            }
            else if (*(regs[dest]) > (stoi(src))) {
                jumps["je"] = false;
                jumps["jne"] = true;
                jumps["jl"] = false;
                jumps["jle"] = false;
                jumps["jg"] = true;
                jumps["jge"] = true;
                jumps["jz"] = false;
                return;
            }
        } 
        else if (src == "0") {
            jumps["jz"] = true;
            return;
        }
        if (check_reg(src) && src != "0") {
            if (*(regs[dest]) == *(regs[src])) {
                jumps["je"] = true;
                jumps["jne"] = false;
                jumps["jl"] = false;
                jumps["jle"] = true;
                jumps["jg"] = false;
                jumps["jge"] = true;
                jumps["jz"] = false;
                return;
            }
            else if (*(regs[dest]) < *(regs[src])) {
                jumps["je"] = false;
                jumps["jne"] = true;
                jumps["jl"] = true;
                jumps["jle"] = true;
                jumps["jg"] = false;
                jumps["jge"] = false;
                jumps["jz"] = false;
                return;
            }
            else if (*(regs[dest]) > *(regs[src])) {
                jumps["je"] = false;
                jumps["jne"] = true;
                jumps["jl"] = false;
                jumps["jle"] = false;
                jumps["jg"] = true;
                jumps["jge"] = true;
                jumps["jz"] = false;
                return;
            }
        } 
        else if (*(regs[src]) == 0) {
            jumps["jz"] = true;
            return;
        }
    } else {
        throw std::runtime_error("Register is not found");
    }
}

void FCPU::jmp(std::string& dest, std::string& src) {
    //std::cout << "R1 " << this->r1 << std::endl << "R2 " << this->r2 << std::endl;
    this->file.seekg(this->label[dest]);
}

void FCPU::je(std::string& dest, std::string& src) {
    if (jumps["je"]) {
        this->file.seekg(this->label[dest]);
    }
}

void FCPU::jl(std::string& dest, std::string& src) {
    if(jumps["jl"]) {
        this->file.seekg(this->label[dest]);
    }
}

void FCPU::jle(std::string& dest, std::string& src) { 
    if (jumps["jle"]) {
        this->file.seekg(this->label[dest]);
    }
}

void FCPU::jg(std::string& dest, std::string& src) {
    if (jumps["jg"]) {
        this->file.seekg(this->label[dest]);
    }
}

void FCPU::jge(std::string& dest, std::string& src) {
    if (jumps["jge"]) {
        this->file.seekg(this->label[dest]);
    }
}

void FCPU::jz(std::string& dest, std::string& src) {
    if (jumps["jz"]) {
        this->file.seekg(this->label[dest]);
    }
}

void FCPU::jne(std::string& dest, std::string& src) {
    if (jumps["jne"]) {
        this->file.seekg(this->label[dest]);
    }
}

void FCPU::print() {
    for (auto it : regs) {
        std::cout << it.first << " " << *it.second << std::endl;
    }
}
