# Recover-RAW-JPEG
*This is one of the CS50 projects that I did* 

This program can recovers JPEGs from a forensic image

This program is meant for practice in pset4 of CS50x. One of the course from Harvard University.

BACKGROUND:

Even though JPEGs are more complicated than BMPs, JPEGs have “signatures,” patterns of bytes that can distinguish them from other file formats. Specifically, the first three bytes of JPEGs are

```
0xff 0xd8 0xff
```

from first byte to third byte, left to right. The fourth byte, meanwhile, is either ```0xe0```, ```0xe1```, ```0xe2```, ```0xe3```, ```0xe4```, ```0xe5```, ```0xe6```, ```0xe7```, ```0xe8```, ```0xe9```, ```0xea```, ```0xeb```, ```0xec```, ```0xed```, ```0xee```, or ```0xef```. Put another way, the fourth byte’s first four bits are ```1110```.

Odds are, if you find this pattern of four bytes on media known to store photos (e.g., my memory card), they demarcate the start of a JPEG. To be fair, you might encounter these patterns on some disk purely by chance, so data recovery isn’t an exact science.

Fortunately, digital cameras tend to store photographs contiguously on memory cards, whereby each photo is stored immediately after the previously taken photo. Accordingly, the start of a JPEG usually demarks the end of another. However, digital cameras often initialize cards with a FAT file system whose “block size” is 512 bytes (B). The implication is that these cameras only write to those cards in units of 512 B. A photo that’s 1 MB (i.e., 1,048,576 B) thus takes up 1048576 ÷ 512 = 2048 “blocks” on a memory card. But so does a photo that’s, say, one byte smaller (i.e., 1,048,575 B)! The wasted space on disk is called “slack space.” Forensic investigators often look at slack space for remnants of suspicious data.

IMPLEMENTATION:

Input: ```card.raw```

Execution: ./recover card.raw

Output: 50 images of Harvard University



