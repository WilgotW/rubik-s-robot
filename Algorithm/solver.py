import kociemba

#example:    cube = 'DRLUUBFBRBLURRLRUBLRDDFDLFUFUFFDBRDUBRUFLLFDDBFLUBLRBD'

def solve_cube(cube):
    #convert to string
    cube_string = ""
    for ch in cube:
        cube_string += ch;

    return kociemba.solve(cube_string)
