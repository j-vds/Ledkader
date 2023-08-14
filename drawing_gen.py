'''
started 30/04/2018

'''

import tkinter
import time
import numpy as np

import sys
import os

# WIDTH = 200
# HEIGHT = 200
COLUMNS = 32
ROWS = 8

COLOURS = ["#0c7839", "#5ef2df"]

class DrawScreen(object):
    def __init__(self, tk, canvas, parseddata):
        self.tk, self.canvas = tk, canvas
        self.alive = True
        self.score = 0
        
        self.field = []

        self.reset(loaded=parseddata)

        self.draw()
        
        #self.canvas.bind_all('<Button-1>', self.mouse_down)
        self.canvas.bind('<ButtonRelease-1>', self.mouse_up)
        self.canvas.bind_all('r', self.reset)
        self.canvas.bind_all('d', self.dump)
        self.canvas.bind_all('b', self.dumpBin)


    def reset(self, evt=None, loaded=None):
        self.field = []
        for r in range(ROWS):
            self.field.append(COLUMNS*[0])

        # for _ in range(random.randint(6,8)):
        #     x = random.randint(0,3)
        #     y = random.randint(0,3)
        #     self.plus(x,y)

        if(loaded):
            # not try to fill in squares
            for coords in loaded:
                #abs value 
                x = coords // 8
                
                y = coords % 8

                # even top -> bottom
                if (x % 2 == 1):
                    y = -(y+1) % 8
                self.field[y][x] = 1

        
        self.draw()

    def mouse_up(self, evt):
        x = evt.x // 30
        y = evt.y // 30

        if x < 0 or x > COLUMNS*30 or y < 0 or y > ROWS*30:
            return
    
        self.field[y][x] = (self.field[y][x] + 1)%2

        self.draw()


    def plus(self, x, y):
        for i,j in [(x,y-1),(x-1,y),(x,y),(x+1,y),(x,y+1)]:   
            if i < 0 or j < 0:
                continue
            elif 3 < i or 3 < j:
                continue
            self.field[j][i] ^= 1


    def draw(self):
        canvas.delete("all")
        for row_index, row in enumerate(self.field):
            for col_index, val in enumerate(row):
                self.canvas.create_rectangle(col_index*30,row_index*30,col_index*30+30,row_index*30+30,fill=COLOURS[val])


    def dumpBin(self, evt=None):
        dump_list = np.array(self.field)
        print("{", end='')
        for c in range(COLUMNS):
            if(c%2 == 1):
                print(hex(int(''.join(map(str,dump_list[::-1,c])),2)), end=", ")
            else:
                print(hex(int(''.join(map(str,dump_list[:,c])),2)), end=", ")
        print('}\n')


    def dump(self, evt):
        c = 0
        print()
        # for y, row in enumerate(self.field):
        for x in range(COLUMNS):
            # for x, v in enumerate(row): 
            for y in range(ROWS):
                v = self.field[y][x]
                # pixel is on
                if not(v):
                    continue
                c += 1
                if x % 2:
                    print(hex(x*8+abs(y-7)), end=",")
                else:
                    print(hex(x*8+y), end=',')
        print(c)


if __name__ ==  "__main__":
    parseddata = None
    if(len(sys.argv) > 1):
        # try to load file
        if os.path.exists(sys.argv[-1]):
            with open(sys.argv[-1], "r") as infile:
                data = [i.strip() for i in infile.readlines()]
                parseddata = list(map(lambda x : int(x,16), "".join(data).split(',')[1:]))

    
    tk = tkinter.Tk()
    tk.resizable(0,0)
    tk.title('plus+')
    tk.wm_attributes('-topmost', 1)
    canvas = tkinter.Canvas(tk, width=30*COLUMNS+1, height=30*ROWS+1, bd=0, highlightthickness=0)
    canvas.pack()
    k = DrawScreen(tk, canvas, parseddata)

    # menu = tkinter.Menu(tk)
    # tk.config(menu=menu)

    while k.alive:
        try:
            tk.update()
            tk.update_idletasks()
        except:
            break

    # time.sleep(2)
    # tk.destroy()
        

    

