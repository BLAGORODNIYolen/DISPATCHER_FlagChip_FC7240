import os
import re
import time

def Add_Include(filePath,name):
    fp = open(filePath)
    lines = []
    for line in fp:
        lines.append(line)
    fp.close()
    fp.close()

    del lines[:2]    #delete previous define DRIVER_xxx_H 
    lines.insert(0, r'#ifndef _'+name.upper()+'_H_') #add in LINE+1
    lines.insert(1, r'#define _'+name.upper()+'_H_') #add in LINE+1
    lines.insert(2, r'#ifdef __cplusplus') #add in LINE+1
    lines.insert(3, r' extern "C" {') #add in LINE+1
    lines.insert(4, r'#endif') #add in LINE+1
     
    lines.insert(len(lines)-1, r'#ifdef __cplusplus') #add in LINE+1
    lines.insert(len(lines)-1, r'}') #add in LINE+1
    lines.insert(len(lines)-1, r'#endif') #add in LINE+1
   
    s = '\n'.join(lines)
    fp = open(filePath, 'w')
    fp.write(s)
    fp.close()


if __name__=='__main__':
    path = os.getcwd()
    for filename in os.listdir(path):
        result1 = os.path.splitext(filename)
        #print(filename+', '+result1[0]+'\n')
        
        if result1[1] == '.h' :
            oldname=filename
            print(filename[7:-9])
            #time.sleep()
            newname='fc7240_'+filename[7:-9].lower()+'_regs.h'
            os.rename(oldname,newname);
            result1 = os.path.splitext(newname)
            Add_Include(newname,result1[0])
            #print(newname+'\n')
