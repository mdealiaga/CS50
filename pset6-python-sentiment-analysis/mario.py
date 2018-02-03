while True:
    p_height = input("How tall do you want the pyramids to be? (Max is 23): ")
    p_height = int(p_height)
    if (p_height <= 23 and p_height >0):
        break
    else:
        print("The maximum height is 23")

for i in range(p_height):
    print(" "*(p_height-i), end="")
    print("#"*(i+1), end="")
    print("  ", end="")
    print("#"*(i+1), end="")
    print("")