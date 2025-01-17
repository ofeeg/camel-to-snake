import os

def snake_case_conversion(ascii_val, str_to_edit, index):
    newstr = list(str_to_edit)
    newstr[index] = chr(ascii_val)
    newstr.insert(index, "_")
    return "".join(newstr)
    

def main():
    while(1):
        dir_to_search = "/home/mrhan/projects/camel-to-snake/test/"#input("Input the directory to iterate.")
        if(type(dir_to_search) != str):
            break
        for filename in os.listdir(dir_to_search):
            if filename.endswith(".py") or filename.endswith(".cc"):
                edited_file = []
                with open(filename, "r") as f:
                    for line in f.readlines():
                        n = 0
                        for word in line.split():
                            i = 0
                            for char in word:
                                ascii_rep = ord(char) + 32
                                print(ascii_rep)
                                if ascii_rep >= 97 and ascii_rep <= 122:
                                    word = snake_case_conversion(ascii_rep, word, i)
                                    i+=1
                                i+=1
                            edited_file.append(word+" ")
                            n+=1
                            if n == len(line.split()):
                                edited_file.append("\n")
                edits = open(filename, "w")
                edits.write("".join(edited_file))
                edits.close()
                        
        break
    return
main()
                            
                        

