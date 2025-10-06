
#pragma once

#include<sstream>

#include "parser.hh"

class Generator {
    public:
        inline Generator(node::Exit root)
            : m_root(std::move(root))
        {

        }

        [[nodiscard]] std::string generate_asm() {
            std::stringstream output;

            output << "global _start\n_start:";
            output << "\tmov rax, 60\n";
			output << "\tmov rdi, " << m_root.expr.int_lit.val.value() << "\n";
			output << "\tsyscall\n";

            return output.str();
        }
    private:
        const node::Exit m_root;
};