// Copyright 2021 NNTU-CS
#include <string>
#include "tstack.h"

int pr(char c) {
  switch (c) {
    case '(':
      return 0;
    case ')':
      return 1;
    case '+':
    case '-':
      return 2;
    case '*':
    case '/':
      return 3;
    default:
      return -1;
  }
}

std::string infx2pstfx(std::string inf) {
  TStack <char> stack;
  std::string res;
  for (int i = 0; i < inf.length(); i++) {
    if ((inf[i] >= '0') && (inf[i] <= '9')) {
      res += inf[i];
      res += ' '; }
    else if (inf[i] == '(') {
      stack.push(inf[i]); }
    else if (pr(inf[i]) > pr(stack.get()) || stack.isEmpty()) {
      stack.push(inf[i]); }
    else if (inf[i] == ')') {
      while (!stack.isEmpty() && stack.get() != '(') {
        res += stack.get();
        res += ' ';
        stack.pop(); }
      if (stack.get() == '(') {
        stack.pop(); }
    }
    else {
      while (!stack.isEmpty() && pr(stack.get()) >= pr(inf[i])) {
        res += stack.get();
        res += ' ';
        stack.pop(); }
      
      stack.push(inf[i]); }
  }

  while (!stack.isEmpty()) {
    res += stack.get();
    res += ' ';
    stack.pop(); }

  while (res[res.length() - 1] == ' ') {
    res = res.substr(0, res.length()-1);
  }

  return res;
}

int eval(std::string pst) {
  TStack <int> stack;

  for (int i = 0; i < pst.length(); i++) {
    if ((pst[i] >= '0') && (pst[i] <= '9')) {
      stack.push(pst[i] - '0'); }
    else if (pst[i] != ' ') {
      int a = stack.get();
      stack.pop();
      int b = stack.get();
      stack.pop();

      if (pst[i] == '-') {
        stack.push(b - a); }
      else if (pst[i] == '+') {
        stack.push(b + a); }
      else if (pst[i] == '*') {
        stack.push(b * a); }
      else {
        stack.push(b / a);
      }
    }
  }
  return stack.get();
}
