/*
 * Reference: http://www.indiana.edu/~iulg/trm/
 *
 * Instruction set
 * ===============
 * Add 1 to Rn   : 1^n#
 *   Rn.push(1)
 *
 * Add # to Rn   : 1^n##
 *   Rn.push(#)
 *
 * Go forward n  : 1^n###
 *   pc += n
 * Go backward n : 1^n####
 *   pc -= n
 *
 * Cases on Rn   : 1^n#####
 *   if Rn.empty(), pc += 1
 *   if Rn.pop() == 1, pc += 2
 *   if Rn.pop() == #, pc += 3
 */

#include <iostream>
#include <map>
#include <queue>
#include <string>

using namespace std;

enum code {
    O,
    H
};

enum op {
    Add1 = 1,
    Add0 = 2,
    Inc = 3,
    Dec = 4,
    Case = 5
};

struct instr {
    op o;
    int n;
};

map< int, instr > program;
map< int, queue<code> > mem;

void push(int i, code c) {
    mem[i].push(c);
}

int cases(int i) {
    queue<code>& Rn = mem[i];
    if (Rn.empty()) {
        return 1;
    } else if (Rn.front() == O) {
        Rn.pop();
        return 2;
    } else if (Rn.front() == H) {
        Rn.pop();
        return 3;
    }
}

void print_registers() {
    for (map< int, queue<code> >::iterator it=mem.begin(); it != mem.end(); it++) {
        cout << "R" << it->first << ":";
        queue<code> content = it->second;
        while (content.empty() == false) {
            code c = content.front();
            content.pop();
            if (c == O) {
                cout << "1";
            } else {
                cout << "#";
            }
        }
        cout << "\n";
    }
}

string op2string(op o) {
    switch (o) {
        case Add1: return "Add1";
        case Add0: return "Add#";
        case Inc:  return "Inc";
        case Dec:  return "Dec";
        case Case: return "Case";
    }
}

string instr2string(instr in) {
     return op2string(in.o) + " " + to_string(in.n);
}
    
void print_program() {
    for (map< int, instr >::iterator it = program.begin(); it != program.end(); it++) {
        cout << it->first << ":"  << instr2string(it->second) << "\n";
    }
}

void eval(int pc) {
    while (program.count(pc)) {
        instr in = program[pc];
        //cout << "pc:" + to_string(pc) + " " + "instr: " + instr2string(in) << "\n";
        switch (in.o) {
            case Add1:
                push(in.n, O);
                pc++;
                break;

            case Add0:
                push(in.n, H);
                pc++;
                break;

            case Inc:
                pc += in.n;
                break;

            case Dec:
                pc -= in.n;
                break;

            case Case:
                pc += cases(in.n);
                break;
        }
    }
}
    
void load_program() {
    cin.sync_with_stdio(false);
    
    char curr;
    instr in;

    in.n = 0;
    int c = 0;
    
    while (cin >> curr) {
        if (curr == '1') {
            if (c > 0) {
                in.o = (op)c;
                program[ program.size() + 1 ] = in;
                in.n = 0;
                c = 0;
            }
            in.n++;
        } else if (curr == '#') {
            c++;
        }
    }
    in.o = (op)c;
    program[ program.size() + 1 ] = in;
}

int main() {
    load_program();
    //print_program();
    eval(1);
    print_registers();
    return 0;
}
