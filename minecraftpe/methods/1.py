
import re

with open("test", "r") as f:
	while (s := f.readline()):
		a = s.split("\t")
		if len(a) > 10:
			name = a[0]
			rg = "^([A-z|0-9]*)::(.*)"
			r = re.search(rg, name)
			if r is None:
				print(a, "has no matches!")
				with open("failed", "a") as ff:
					ff.write(str(a)+"\n")
				continue
			clz = r.group(1)
			args = r.group(2)
			#print(clz, args)
			with open(clz+".map", "a") as ff:
				ff.write(args+"\n")
