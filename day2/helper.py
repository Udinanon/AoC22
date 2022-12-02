from itertools import product
# scores R1 P2 S3
# AR BP CS
values = ["0+3;",#ax
          "3+1;",#ay
          "6+2;",#az
          "0+1;",#bx
          "3+2;",#by
          "6+3;",#bz
          "0+2;",#cx
          "3+3;",#cy
          "6+1;"
          ]
count = 0
with open("out.txt", "w") as file_writer:
    for i in product(["A", "B", "C"], ["X", "Y", "Z"]):
        file_writer.writelines(f"""      else if(data[0] == '{i[0]}' && data[2] == '{i[1]}') {{
            score += {values[count]}
        }}    
""")
        count+=1