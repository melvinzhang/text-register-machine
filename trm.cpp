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
#include <string>
#include <map>
#include <vector>
#include <queue>

using namespace std;

enum Code {
    O,
    H
};

enum Op {
    Add1 = 1,
    Add0 = 2,
    Inc  = 3,
    Dec  = 4,
    Case = 5
};

struct Instr {
    Op op;
    int n;
};

struct TRM {
    vector< Instr > program;
    map< int, queue<Code> > mem;

    void push(int i, Code c) {
        mem[i].push(c);
    }

    int cases(int i) {
        queue<Code>& Rn = mem[i];
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
        for (map< int, queue<Code> >::iterator it=mem.begin(); it != mem.end(); it++) {
            cout << "R" << it->first << ":";
            queue<Code> content = it->second;
            while (content.empty() == false) {
                Code c = content.front();
                content.pop();
                if (c == O) {
                    cout << "1";
                } else {
                    cout << "#";
                }
            }
            cout << endl;
        }
    }

    string op2string(Op o) {
        switch (o) {
            case Add1: return "Add1";
            case Add0: return "Add#";
            case Inc:  return "Inc";
            case Dec:  return "Dec";
            case Case: return "Case";
        }
    }

    string instr2string(Instr in) {
         return op2string(in.op) + " " + to_string(in.n);
    }
        
    void print_program() {
        for ( auto &p : program) {
            cout << instr2string(p) << endl;
        }
    }

    void eval(int pc) {
        while (pc < program.size()) {
            Instr in = program[pc];
            //cout << "pc:" + to_string(pc) + " " + "instr: " + instr2string(in) << endl;
            switch (in.op) {
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

        int n = 0;
        int c = 0;
        
        while (cin >> curr) {
            if (curr == '1') {
                if (c > 0) {
                    n = 0;
                    c = 0;
                }
                n++;
            } else if (curr == '#') {
                c++;
                if (c == 1) {
                    program.push_back({Add1, n});
                } else {
                    program.back().op = (Op)c;
                }
            }
        }
    }
};



int main() {
    TRM m;
    m.load_program();
    m.print_program();
    m.eval(0);
    m.print_registers();
    return 0;
}
