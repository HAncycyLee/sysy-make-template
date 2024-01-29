#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <cassert>
#include <vector>
#include <map>
#include <variant>


using namespace std;

// basic class for AST

class BaseAST {
		public:
				virtual ~BaseAST() = default;


				virtual void Dump() const = 0;
};

class CompUnitAST : public BaseAST {
		public:
				std::unique_ptr<BaseAST> func_def;

				void Dump() const override {
					std::cout << "CompUnitAST { ";
					func_def->Dump();
					std::cout << " } ";
				  }
};

class FuncDefAST : public BaseAST {
		public:
				std::unique_ptr<BaseAST> func_type;
				std::string ident;
				std::unique_ptr<BaseAST> block;
				
				void Dump() const override {
					std::cout << "FuncDefAST { ";
					func_type->Dump();
					std::cout << ", " << ident << ", ";
					block->Dump();
					std::cout << " } ";
				  }
};

class FuncTypeAST : public BaseAST {
		public:
				std::string ident;

				void Dump() const override {
					std::cout << "FuncTypeAST { ";
					std::cout << ident;
					std::cout << " } ";
				}
};

class BlockAST : public BaseAST {
		public:
				std::unique_ptr<BaseAST> stmt;	

				void Dump() const override {
						std::cout << "BlockAST { ";
						stmt->Dump();
						std::cout << " } ";
				}
};

class StmtAST : public BaseAST {
		public:
				std::unique_ptr<BaseAST> number;

				void Dump() const override {
						std::cout << "StmtAST { ";
						number->Dump();
						std::cout << " } ";
				}
};

class NumberAST : public BaseAST {
		public:
				std::string ident;

				void Dump() const override {
						std::cout << "NumberAST { ";
						std::cout << ident;
						std::cout << " } ";
				}
};
