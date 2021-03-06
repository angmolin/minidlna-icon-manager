# minidlna-icon-manager
Extract or embed an icon to minidlna application

These two applications can help you extracting and embeding custom images to minidlna code.

To compile the extractor:<br>
`gcc minidlna-icon-extract.c -o minidlna-icon-extract`

To extract an embeded image copy the image string array to a file. It should look like this:<br>
`"\x89\x50\x4e\x47\x0d\x0a\x1a\x0a\x00\x00\x00\x0d\x49\x48\x44\x52\x00\x00\x00\x29\x00\x00\x00\x30"`<br>
`"\x08\x06\x00\x00\x00\x8c\xb9\x53\xa5\x00\x00\x00\x01\x73\x52\x47\x42\x00\xae\xce\x1c\xe9\x00\x00"`<br>
`"\x08\xf3\x49\x44\x41\x54\x58\xc3\xc5\x99\x7b\x6c\x53\xd7\x19\xc0\x7f\xf7\x5e\x3f\x62\xe7\x69\x02"`<br>
`"\x24\x4b\x52\xe2\x84\x24\x24\x24\x83\x50\x5a\x06\x6b\x80\x96\x74\xa5\x1b\x63\xd5\xe8\xd6\x69\x65"`<br>
`..................................................................................................`<br>
`"\xc5\xb7\x8f\x85\x8b\x71\xbd\xcb\x01\x73\x1c\xa0\x39\x0e\x30\x11\x32\x06\x1a\xeb\x24\x98\xb0\x57"`<br>
`"\x8d\x07\x34\x27\x0c\x34\x76\xc1\x1f\xaf\x23\x18\x05\x34\x6e\xe6\x06\x23\x06\xa8\xc4\x41\xc6\x0e"`<br>
`"\x4d\x32\x41\x1d\x6a\x9c\x25\x8d\xb8\x32\xa6\xfc\x1f\xc3\xda\x5b\x26\xd2\x1f\x78\xac\x00\x00\x00"`<br>
`"\x00\x49\x45\x4e\x44\xae\x42\x60\x82"`<br>

Now execute the extractor with:<br>
`minidlna-icon-extract <file with string array> output.png`<br>

To compile the embeder:<br>
`gcc minidlna-icon-embed.c -o minidlna-icon-embed`<br>

To embed an png image just execute:<br>
`minidlna-icon-embed <png file> output.bin`<br>

And finally copy the contents of this new file to the minidlna string array.
