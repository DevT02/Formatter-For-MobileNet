# MobileNetV2 Formatter
> Compiles images into directories usable for mobilenetv2ssd training as well as the required text files. AKA "prepare a dataset." **This does not create labels (labels.txt)**. Usage intended for 
[PytorchSSD](https://github.com/qfgaohao/pytorch-ssd/), which is implemented into the [NVIDIA Jetson](https://github.com/dusty-nv/jetson-inference) trainer.

## Notice
```diff
- You must manually drag your labels.txt file into both directories. 
- Because this program moves images/files, antiviruses will likely flag it as malicious. Just exclude the program.
+ Files are split based on 70& for training, 20% for validation, and 10% for testing.  
```
If you wish to change the percent distribution:
https://github.com/DevT02/formatterForMobileNetV2/blob/0c514761563a4d61fe5d55ce51a142c0b39d87d2/compileFormatter/compileFormatter.cpp#L75-L77
# Passing Parameters
## Format: ``compileFormatter.exe --pname --vpname --idirect --ext --outdir``
```
--pname : Name for Model
--idirect : Image Directory Absolute Path
--ext : File Extension of Images (CASE SENSITIVE)
--outdir : Folder to Output (doesn't need specific directory)
--pytorch : Include this if you're making this run for the pytorch-ssd
--vpname : Name for Model Validation (only if --pytorch)
```
&nbsp;
## Essentially,

```compileFormatter.exe --pname ModelName --idirect "PathToDir" --ext .JPG --outdir "PathToDir"```

```compileFormatter.exe --pname ModelName --idirect "PathToDir" --ext .JPG --outdir OutputName```

&nbsp;

## or with Pytorch
```compileFormatter.exe --pname Name --idirect "PathToDir" --ext .JPG --outdir "PathToDir" --pytorch --vpname ValidationModelName```

```compileFormatter.exe --pname Name --idirect "PathToDir" --ext .JPG --outdir OutputName --pytorch --vpname ValidationModelName```


&nbsp;
## Examples:

```compileFormatter.exe --pname test --idirect "D:\Program Files\Microsoft Visual Studio Files\mobileNetFormatter\formatterForMobileNetV2\Debug\data" --ext .JPG --outdir "D:\Program Files\Microsoft Visual Studio Files\mobileNetFormatter\formatterForMobileNetV2\Debug\output"```


```compileFormatter.exe --pname test --idirect "D:\Program Files\Microsoft Visual Studio Files\compileFormatter\compileFormatter\Debug\data" --ext .JPG --outdir output --pytorch --outdir outputFolder```





Here is an old screenshot of the command line with it running, it may not be up-to-date:

![commandline](https://user-images.githubusercontent.com/40608267/200220476-f381d9d8-f1bf-40ce-92a9-03fd8f60afee.png)



