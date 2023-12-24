for a in range(2):
    for b in range(2):
        for c in range(2):
            if (not a or b or c) and (a or not b or c) and (b or not c) and (not a or not b):
                print("TRUE")
            else:
                print("FALSE")
            print("a = %d, b = %d, c = %d" % (a, b, c))