import os

impl = "impl"
head = "headers"
def getfiles(arr, dir):
	for f in os.listdir(dir):
		file = f"{dir}/{f}"
		if(os.path.isdir(file)):
			getfiles(arr, file)
		else:
			arr.append(file)
	return arr

implf = getfiles([], impl)
implfs = set()
for f in implf:
	ff = ".".join(f.split("/")[-1].split(".")[:-1])
	implfs.add(ff)
headf = getfiles([], head)
print("impl:", len(implf))
print("head:", len(headf))
for f in headf:
	ff = ".".join(f.split("/")[-1].split(".")[:-1])
	if ff not in implfs:
		print(f)
