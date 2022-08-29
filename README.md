# minishell for cursus 42

## 1. :subject
creation of mini-real bash prompt


## 2:lien utile pour comprendre:
Bash Reference Manual : 
https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Command-Search-and-Execution


## 3. How to execute?
- .1 do **make**
- .2 execute **./minishell**
- .3 write your command on prompt

***/!\ for check the real mouvement of bash, do test under the
conditon bash posix.*** 
-> write in prompt like this:
**bash --posix**



## 4. Parsing
#### 1 Lexer
-  Separation commande_line
-  Quote close and quoting rules
-  Tokenization (separation of word in commande_line) 
-  checking type of word in token

#### 2 Parser 
- Using BNF (Forme de Backus-Naur) for parsing 
- what is BNF? https://fr.wikipedia.org/wiki/Forme_de_Backus-Naur 
- good resource for study recursion from 42 student : 
  https://github.com/0xbatche/parser-bison

#### 3 Expansion word 
- expansion variable environement
- remove quotting
- generte pathname

## 5. Redirection
- Pipe
- Open / Close file
- Heredocument

## 6. Builtin
- echo (with -n option)
- export
- unset
- env
- pwd
- cd
- exit

## 7. signal
- Ctrl + C
- Ctrl + \

## 8.Exection (in work)
-
- 
-

