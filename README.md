# Signatures-Detector

Simple signature detector application which contains of the following two components:
* Scanner: core component, implemented as a separate server process.
* GUI application.

Scanner description
Scanner component :
* Scan file by path;
* Scan array of bytes.

Malware detection algorithm: if scanned file contains any of predefined byte sequences, it is considered infected. The sequences are stored in the regular text file separated by newlines, in the following format:
HexString.{GUID}

Examples:
01ABEDFF55.{ab306a70-0fd2-4b4b-84fe-f9ebd899d90f}
EE21DEAD827739ACCD028FFC.{5c34b10f-3f6d-4bbb-b9ec-2faa1ee07660}
If appropriate sequence is found, scanner  returns its GUID. Scanner uses file mapping to increase scanning performance.

GUI application description
* Application able to use scanner component to recursively scan specific folder.
* Scanning progress must be displayed in the progress bar control.
