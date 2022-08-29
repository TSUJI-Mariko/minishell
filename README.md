# minishell for cursus 42

#1 :but o'objet

## 2:lien utile pour comprendre:
Bash Reference Manual : 
https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Command-Search-and-Execution



## 3. Parsing
### .1 Lexer
-  Separation commande_line
-  Quote close and quoting rules
-  Tokenization (separation of word in commande_line) 
-  checking type of word in token

### .2 Parser 
- Using BNF (Forme de Backus-Naur) for parsing 
- what is BNF? https://fr.wikipedia.org/wiki/Forme_de_Backus-Naur 
- good resource for study recursion from 42 student : 
  https://github.com/0xbatche/parser-bison

### .3 Expende word 
- expend variable environement
- remove quotting
- generte pathname

## 4. Redirection
- Pipe
- Open / Close file
- Heredocument

## 5. Builtin
- echo (with -n option)
- export
- unset
- env
- pwd
- cd
- exit

## 6. signal
- Ctrl + C
- Ctrl + \

## 7.Exection (in work)
-
- 
-


## 8. How to work?

- 1. do **make**
- 2. execute **./minishell**
- 3. write your command on prompt!


/!\ for check the real mouvement of bash, do test under the
conditon bash posix. 

###-> write in prompt like this:
**bash --posix**
