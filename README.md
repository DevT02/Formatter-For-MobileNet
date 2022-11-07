# MobileNetV2 Formatter
> Compiles all images into directories usable for mobilenetv2ssd training

# Passing Parameters
## Format: ``compileFormatter.exe --pname --vpname --idirect --ext --outdir``
```
--pname : Name for Model
--vpname : Name for Model Validation
--idirect : Image Directory Absolute Path
--ext : File Extension of Images (CASE SENSITIVE)
--outdir : Folder to Output (doesn't need specific directory)
```
&nbsp;
## Essentially,

```compileFormatter.exe --pname Name  --vpname NameValid --idirect "PathToDir" --ext .JPG --outdir "PathToDir"```

```compileFormatter.exe --pname Name --vpname NameValid --idirect "PathToDir" --ext .JPG --outdir OutputName```
&nbsp;
## Notice
```diff
- You must manually drag your labels.txt file into both directories. 
- Because this program moves images/files, antiviruses will likely flag it as malicious. Just exclude the program.
```
&nbsp;
## Examples:

```compileFormatter.exe --pname test --vpname testvalid --idirect "D:\Program Files\Microsoft Visual Studio Files\mobileNetFormatter\formatterForMobileNetV2\Debug\data" --ext .JPG --outdir "D:\Program Files\Microsoft Visual Studio Files\mobileNetFormatter\formatterForMobileNetV2\Debug\output"```


```compileFormatter.exe --pname test --vpname testvalid --idirect "D:\Program Files\Microsoft Visual Studio Files\compileFormatter\compileFormatter\Debug\data" --ext .JPG --outdir output```





Here is a screenshot of the command line with it running:

![commandline](https://user-images.githubusercontent.com/40608267/200220476-f381d9d8-f1bf-40ce-92a9-03fd8f60afee.png)



