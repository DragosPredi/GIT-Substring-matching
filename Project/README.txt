!!ENUNT:
Git ​ is a source code control system, a crucial tool used in software development to track the
changes of a set of files over time.This information is stored in a special data structure called a
repository.

The​ Git repository​ is stored in a subdirectory, called ​ .git​ , of the project directory (also called
the root directory). The repository consists mainly of ​ commits ​ (a commit is a set of file changes).
Let us consider a ​ case insensitive ​ file system (meaning that “ ​ C:\file.txt”​ and ​ “C:\FilE.tXt”​ are
the same path). The file changes in a commit we will focus on are:

● Additions ​ - files which are absent in the previous commit, but present in the current commit
● Modifications ​ - files which are present in both the previous and the current commit, but have
different content / modified date (for simplicity a ​ date ​ will be an ​ unsigned integer ​ / a
timestamp​ ).
● Deletions ​ - files which are present in the previous commit, but absent in the current commit

To compute the differences, Git needs to compare the current project revision with the
previous project revision. However, we need to also test our code before making a git commit. This
means that we need to compile the code. As a result, many object files are created. By default, when
scanning the filesystem git adds these files to the changes for the next commit we make.

Do we need to discard the addition of these files? No, we can do something better. We can
specify a ​ .gitignore​ ​ configuration file. When Git detects a changed file, it tries to match the path
of the changed file with one of the rules specified in the ​ .gitignore​ file. If one rule is applied
successfully, the changed file is ignored.

For simplicity, our only rule for excluding a file is ​ case insensitive substring matching
between the path of the file and any of the strings in the ​ .gitignore​ file.

!!TASK-URI:

1)You are required to compute the changes (which files are added, modified and deleted) between two
consecutive revisions of the project (commits).
2)You are required to update the algorithm to filter the results you output in the 3 files above (added.out,
modified.out, deleted.out) using information from a ​ .gitignore​ ​ file.
Our rule for ignoring a changed file is ​ case insensitive substring matching​ between the ​ path of the
changed file​ and ​ any​ of the strings defined in the ​ .gitignore​ file.
In other words, if a string in the ​ .gitignore​ file is a substring of the changed file’s path, that file is
ignored.
3)There are other ways of specifying rules for the file. Consider a ​ .gitignore​ file consisting of
regular expressions. ​ A changed file is ignored if its path is matched by any of the regular
expressions. Your task is to update the algorithm to perform ​ case insensitive regular expression
matching instead of case insensitive substring matching.



Tinand cont de faptul ca se fac multe cautari pe string-uri m-am gandit
ca cea mai eficienta structura de date este o Trie.
Dar tinand cont ca trie foloseste multa memorie, am creat Trie cu alllowercase pentru
a injumatati memoria folosita desi se va pierde timp la transformarea string-urilor.

Pentru rezolvare creez 2 vectori de string-uri (previous si current) care sunt creati 
in functie de task tinand cont de (git ignore sau git ignore regex). Creez Trie cu previous.
Si o parcurg de 2 ori, o data cu current pentru a gasi modified si added si o data cu previous pentru a gasi deleted.

Pentru rulare pe linux am inclus un makefile cu regulile build, run si clean.
