from itertools import product
values = ["score += 3+1;",
          "score += 6+2;",
          "score += 0+3;",
          "score += 0+1;",
          "score += 3+2;",
          "score += 6+3;",
          "score += 0+1;",
          "score += 6+2;",
          "score += 3+3;"
          ]
count = 0
with open("out.txt", "w") as file_writer:
    for i in product(["A", "B", "C"], ["X", "Y", "Z"]):
        file_writer.writelines(f"""      else if(data[0] == '{i[0]}' && data[2] == '{i[1]}') {{
            {values[count]}
        }}    
""")
        count+=1