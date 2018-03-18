#include "textprocessor.h"


/*
  Name  : CRC-32
  Poly  : 0x04C11DB7    x^32 + x^26 + x^23 + x^22 + x^16 + x^12 + x^11 
                       + x^10 + x^8 + x^7 + x^5 + x^4 + x^2 + x + 1
  Init  : 0xFFFFFFFF
  Revert: true
  XorOut: 0xFFFFFFFF
  Check : 0xCBF43926 ("123456789")
  MaxLen: 268 435 455 байт (2 147 483 647 бит) - обнаружение
   одинарных, двойных, пакетных и всех нечетных ошибок
*/
const uint_least32_t Crc32Table[256] = {
    0x00000000, 0x77073096, 0xEE0E612C, 0x990951BA,
    0x076DC419, 0x706AF48F, 0xE963A535, 0x9E6495A3,
    0x0EDB8832, 0x79DCB8A4, 0xE0D5E91E, 0x97D2D988,
    0x09B64C2B, 0x7EB17CBD, 0xE7B82D07, 0x90BF1D91,
    0x1DB71064, 0x6AB020F2, 0xF3B97148, 0x84BE41DE,
    0x1ADAD47D, 0x6DDDE4EB, 0xF4D4B551, 0x83D385C7,
    0x136C9856, 0x646BA8C0, 0xFD62F97A, 0x8A65C9EC,
    0x14015C4F, 0x63066CD9, 0xFA0F3D63, 0x8D080DF5,
    0x3B6E20C8, 0x4C69105E, 0xD56041E4, 0xA2677172,
    0x3C03E4D1, 0x4B04D447, 0xD20D85FD, 0xA50AB56B,
    0x35B5A8FA, 0x42B2986C, 0xDBBBC9D6, 0xACBCF940,
    0x32D86CE3, 0x45DF5C75, 0xDCD60DCF, 0xABD13D59,
    0x26D930AC, 0x51DE003A, 0xC8D75180, 0xBFD06116,
    0x21B4F4B5, 0x56B3C423, 0xCFBA9599, 0xB8BDA50F,
    0x2802B89E, 0x5F058808, 0xC60CD9B2, 0xB10BE924,
    0x2F6F7C87, 0x58684C11, 0xC1611DAB, 0xB6662D3D,
    0x76DC4190, 0x01DB7106, 0x98D220BC, 0xEFD5102A,
    0x71B18589, 0x06B6B51F, 0x9FBFE4A5, 0xE8B8D433,
    0x7807C9A2, 0x0F00F934, 0x9609A88E, 0xE10E9818,
    0x7F6A0DBB, 0x086D3D2D, 0x91646C97, 0xE6635C01,
    0x6B6B51F4, 0x1C6C6162, 0x856530D8, 0xF262004E,
    0x6C0695ED, 0x1B01A57B, 0x8208F4C1, 0xF50FC457,
    0x65B0D9C6, 0x12B7E950, 0x8BBEB8EA, 0xFCB9887C,
    0x62DD1DDF, 0x15DA2D49, 0x8CD37CF3, 0xFBD44C65,
    0x4DB26158, 0x3AB551CE, 0xA3BC0074, 0xD4BB30E2,
    0x4ADFA541, 0x3DD895D7, 0xA4D1C46D, 0xD3D6F4FB,
    0x4369E96A, 0x346ED9FC, 0xAD678846, 0xDA60B8D0,
    0x44042D73, 0x33031DE5, 0xAA0A4C5F, 0xDD0D7CC9,
    0x5005713C, 0x270241AA, 0xBE0B1010, 0xC90C2086,
    0x5768B525, 0x206F85B3, 0xB966D409, 0xCE61E49F,
    0x5EDEF90E, 0x29D9C998, 0xB0D09822, 0xC7D7A8B4,
    0x59B33D17, 0x2EB40D81, 0xB7BD5C3B, 0xC0BA6CAD,
    0xEDB88320, 0x9ABFB3B6, 0x03B6E20C, 0x74B1D29A,
    0xEAD54739, 0x9DD277AF, 0x04DB2615, 0x73DC1683,
    0xE3630B12, 0x94643B84, 0x0D6D6A3E, 0x7A6A5AA8,
    0xE40ECF0B, 0x9309FF9D, 0x0A00AE27, 0x7D079EB1,
    0xF00F9344, 0x8708A3D2, 0x1E01F268, 0x6906C2FE,
    0xF762575D, 0x806567CB, 0x196C3671, 0x6E6B06E7,
    0xFED41B76, 0x89D32BE0, 0x10DA7A5A, 0x67DD4ACC,
    0xF9B9DF6F, 0x8EBEEFF9, 0x17B7BE43, 0x60B08ED5,
    0xD6D6A3E8, 0xA1D1937E, 0x38D8C2C4, 0x4FDFF252,
    0xD1BB67F1, 0xA6BC5767, 0x3FB506DD, 0x48B2364B,
    0xD80D2BDA, 0xAF0A1B4C, 0x36034AF6, 0x41047A60,
    0xDF60EFC3, 0xA867DF55, 0x316E8EEF, 0x4669BE79,
    0xCB61B38C, 0xBC66831A, 0x256FD2A0, 0x5268E236,
    0xCC0C7795, 0xBB0B4703, 0x220216B9, 0x5505262F,
    0xC5BA3BBE, 0xB2BD0B28, 0x2BB45A92, 0x5CB36A04,
    0xC2D7FFA7, 0xB5D0CF31, 0x2CD99E8B, 0x5BDEAE1D,
    0x9B64C2B0, 0xEC63F226, 0x756AA39C, 0x026D930A,
    0x9C0906A9, 0xEB0E363F, 0x72076785, 0x05005713,
    0x95BF4A82, 0xE2B87A14, 0x7BB12BAE, 0x0CB61B38,
    0x92D28E9B, 0xE5D5BE0D, 0x7CDCEFB7, 0x0BDBDF21,
    0x86D3D2D4, 0xF1D4E242, 0x68DDB3F8, 0x1FDA836E,
    0x81BE16CD, 0xF6B9265B, 0x6FB077E1, 0x18B74777,
    0x88085AE6, 0xFF0F6A70, 0x66063BCA, 0x11010B5C,
    0x8F659EFF, 0xF862AE69, 0x616BFFD3, 0x166CCF45,
    0xA00AE278, 0xD70DD2EE, 0x4E048354, 0x3903B3C2,
    0xA7672661, 0xD06016F7, 0x4969474D, 0x3E6E77DB,
    0xAED16A4A, 0xD9D65ADC, 0x40DF0B66, 0x37D83BF0,
    0xA9BCAE53, 0xDEBB9EC5, 0x47B2CF7F, 0x30B5FFE9,
    0xBDBDF21C, 0xCABAC28A, 0x53B39330, 0x24B4A3A6,
    0xBAD03605, 0xCDD70693, 0x54DE5729, 0x23D967BF,
    0xB3667A2E, 0xC4614AB8, 0x5D681B02, 0x2A6F2B94,
    0xB40BBE37, 0xC30C8EA1, 0x5A05DF1B, 0x2D02EF8D
};
 
uint_least32_t Crc32(const unsigned char * buf, size_t len)
{
    uint_least32_t crc = 0xFFFFFFFF;
    while (len--)
        crc = (crc >> 8) ^ Crc32Table[(crc ^ *buf++) & 0xFF];
    return crc ^ 0xFFFFFFFF;
}

uint_least32_t crc32(const int32_t fd, const int32_t fileSize, const int32_t RAMLimit)
{
    int32_t size = (RAMLimit > fileSize) ? fileSize : RAMLimit;
    int32_t offset = 0;
    char *addr;

    while (offset < fileSize) {
        addr = (char *)mmap(NULL, (size_t)size, PROT_READ, MAP_PRIVATE, fd, offset);
        if (addr == MAP_FAILED) {
            handle_error("mmap");
        }
        return Crc32(addr, size);
    }
}

void handler(const int32_t derp)
{
    if (derp == 0) {
        printf("use '/PathToFile(if using command) RAMLimitInBytes Command(optional)'\n");
        printf("use '-help' to show this message\n");
        printf("use '-commands' to show commands and parameters\n");
    } else if (derp == 1) {
        printf("Unknown command.\n");
        printf("Use:\n");
        printf("-stats\n");
        printf("-print leftIdx rightIdx\n");
        printf("-search SubString withReg/withoutReg\n");
        printf("-replace OldSubString NewSubString (maybe empty)\n");
    } else if (derp == 2) {
        printf("Use:\n");
        printf("-stats\n");
        printf("-print leftIdx rightIdx\n");
        printf("-search SubString withReg/withoutReg\n");
        printf("-replace OldSubString NewSubString \n");
    }

    exit(0);
}

void menu(const int32_t act)
{
    switch (act) {
        case 0: {
            printf("Avaliable commands:\n");
            printf("0) Choose file\n");
            printf("1) Search substring\n");
            printf("2) Print text\n");
            printf("3) Replace substring\n");
            printf("4) Show stats\n");
            printf("5) Exit\n");
            printf("6) CRC32\n");
            break;
        }
        case 1: {
            printf("Enter substring to search: ");
            break;
        }
        case 2: {
            printf("Enter left and right string idxs to show: ");
            break;
        }
        case 3: {
            break;
        }
        case 4: {
            printf("Enter filename: ");
        break;
        }
        case 5: {
            printf("Unknown command.\n");
            break;
        }
    }
}

void searchWithoutRegistry(const int32_t fd, const int32_t fileSize,  const int32_t RAMLimit, char *subString, const int32_t strSize)
{
    int32_t size = (RAMLimit > fileSize) ? fileSize : RAMLimit;
    int32_t offset = 0, index = 0, bytepos = 1;
    char *addr;

    while (offset < fileSize) {
        addr = (char *)mmap(NULL, (size_t)size, PROT_READ, MAP_PRIVATE, fd, offset);
        if (addr == MAP_FAILED) {
            handle_error("mmap");
        }

        for (int i = 0; i < size; ++i, ++bytepos) {

            if (tolower(addr[i]) == tolower(subString[index])) {
                ++index;
                for (int32_t j = i + 1; (index < strSize) && (j < size); ++index, ++j) {
                    if (tolower(addr[j]) != tolower(subString[index]) || isspace(addr[j])) {
                        index = 0;
                        break;
                    }
                }

                if (index == strSize) {
                    printf("First entry was found at %d byte\n", bytepos);
                    return;
                }
            }
        }

        if (munmap(addr, size) == -1) {
            handle_error("munmap");
        }
        offset += size;
    }
    printf("There is no entries in file\n");
}

void searchWithRegistry(const int32_t fd, const int32_t fileSize,  const int32_t RAMLimit, char *subString, const int32_t strSize)
{
    int32_t size = (RAMLimit > fileSize) ? fileSize : RAMLimit;
    int32_t offset = 0, index = 0, bytepos = 1;
    char *addr;

    while (offset < fileSize) {
        addr = (char *)mmap(NULL, (size_t)size, PROT_READ, MAP_PRIVATE, fd, offset);
        if (addr == MAP_FAILED) {
            handle_error("mmap");
        }

        for (int i = 0; i < size; ++i, ++bytepos) {
            if (addr[i] == subString[index]) {
                ++index;
                for (int32_t j = i + 1; (index < strSize) && (j < size); ++index, ++j) {
                    if (subString[index] != addr[j] || isspace(addr[j])) {
                        index = 0;
                        break;
                    }
                }

                if (index == strSize) {
                    printf("First entry was found at %d byte\n", bytepos);
                    return;
                }
            }
        }

        if (munmap(addr, size) == -1) {
            handle_error("munmap");
        }
        offset += size;
    }
    printf("There is no entries in file\n");
}

void checkLimit(int *userLimit)
{
    int32_t pageSize = sysconf(_SC_PAGESIZE);

    if (*userLimit < pageSize) {
        printf("Your limit is less than page size\n");
        printf("Mmap limit will be set to page size - %d\n", pageSize);
        *userLimit = pageSize;
    } else if ((*userLimit % pageSize) != 0) {
        int32_t count = 0;
        while (*userLimit > pageSize) {
            *userLimit -= pageSize;
            ++count;
        }

        *userLimit = pageSize * count;
    }
}

void print(const int32_t fd, const int32_t fileSize, const int32_t RAMLimit, const int32_t first, const int32_t second)
{
    if (first < 0 || second < 0) {
        printf("Number char must be > 0.\n");
        return;
    }
    int32_t size = (RAMLimit > fileSize) ? fileSize : RAMLimit;
    int32_t offset = 0;
    char *addr;
    bool printed = false;

    while (offset < fileSize) {
        addr = (char *)mmap(NULL, (size_t)size, PROT_READ, MAP_PRIVATE, fd, offset);
        if (addr == MAP_FAILED) {
            handle_error("mmap");
        }
        for (int32_t i = first; i < second && addr[i] != EOF; ++i) {
            putchar(addr[i]);
            printed = true;
        }
        
        if (munmap(addr, size) == -1) {
            handle_error("munmap");
        }

        if (printed) {
            return;
        }

        offset += size;
    }
    if (!printed) {
        printf("Wrong number.\n");
        return;
    }
}

void getStats(const int32_t fd, const int32_t fileSize, const int32_t RAMLimit)
{
    char *addr;
    int32_t offset = 0, bytepos = 1, lines = 1;
    int32_t size = (RAMLimit > fileSize) ? fileSize : RAMLimit;

    while(offset < fileSize) {
        addr = (char *)mmap(NULL, (size_t)size, PROT_READ, MAP_PRIVATE, fd, offset);
        if (addr == MAP_FAILED) {
            handle_error("mmap");
        }

        for (int32_t i = 0; i < size; ++i, ++bytepos) {
            if (addr[i] == '\n') {
                ++lines;
            }
        }

        if (munmap(addr, RAMLimit) == -1) {
            handle_error("munmap");
        }

        offset += RAMLimit;
    }

    if (lines > 1) {
        --lines;
    }

    printf("Amount of symbols - %d\nAmount of lines - %d\n", fileSize, lines);
}

int32_t removeOldString(const int32_t fd, const int32_t fileSize, const int32_t RAMLimit, const int32_t from, const int32_t to)
{
    if ((from < 0) || (to < 0) || (from > to) || (to - 1 > fileSize)) {
        printf("Incorrect bounds.\n");
        return 0;
    }
    int32_t diff = (fileSize == to - 1) ? 1 : fileSize - to;
    char *old = (char *) malloc(sizeof(char) * diff);
    if (old == NULL) {
        handle_error("malloc-");
    }
    int32_t size = (RAMLimit > fileSize) ? fileSize : RAMLimit;
    int32_t offset = 0, bytepos = 1, k = 0;
    char *addr;

    while (offset < fileSize) {
        addr = (char *) mmap(NULL, (size_t)size, PROT_READ, MAP_PRIVATE, fd, offset);
        if (addr == MAP_FAILED) {
            handle_error("mmap");
        }

        for (int32_t i = 0; i < size; ++i, ++bytepos) {
            if (bytepos >= to) {
                old[k] = addr[i];
                ++k;
            }
        }

        if (munmap(addr, size) == -1) {
            handle_error("munmap");
        }

        offset += size;
    }

    int32_t newFileSize = fileSize - to + from;
    if (ftruncate(fd, newFileSize)) {
        handle_error("ftruncate-");
    }

    bytepos = 1, offset = 0, k = 0;
    size = (RAMLimit > newFileSize) ? newFileSize : RAMLimit;

    while(offset < newFileSize) {
        addr = (char *)mmap(NULL, (size_t)size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, offset);
        if (addr == MAP_FAILED) {
            handle_error("mmap");
        }

        for (int32_t i = 0; i < size; ++i, ++bytepos) {
            if (bytepos >= from) {
                addr[i] = old[k];
                ++k;
            }
        }

        if (msync(addr, size, MS_SYNC) == -1) {
            handle_error("msync");
        }

        if (munmap(addr, size) == -1) {
            handle_error("munmap");
        }

        offset += size;
    }

    free(old);
    return newFileSize;
}

void insertNewString(const int32_t fd, const int32_t fileSize, const int32_t RAMLimit, char *string, const int32_t from, const int32_t to)
{
    if ((from < 0) || (to < 0) || (from > to)) {
        printf("Incorrect bounds.\n");
        return;
    }

    char *old = (char*) malloc(sizeof(char) * (fileSize - from));
    if (old == NULL) {
        handle_error("malloc+");
    }
    int32_t size = (RAMLimit > fileSize) ? fileSize : RAMLimit;
    int32_t offset = 0, bytepos = 1, k = 0;
    char *addr;

    while (offset < fileSize) {
        addr = (char *)mmap(NULL, (size_t)size, PROT_READ, MAP_PRIVATE, fd, offset);
        if (addr == MAP_FAILED) {
            handle_error("mmap");
        }

        for (int32_t i = 0; i < size; ++i, ++bytepos) {
            if (bytepos >= from) {
                old[k] = addr[i];
                ++k;
            }
        }

        if (munmap(addr, size) == -1) {
            handle_error("munmap");
        }

        offset += size;
    }

    int32_t newFileSize = fileSize + to - from;
    if (ftruncate(fd, newFileSize)) {
        handle_error("ftruncate+");
    }

    int32_t l = 0;
    bytepos = 1, offset = 0, k = 0;
    size = (RAMLimit > newFileSize) ? newFileSize : RAMLimit;

    while (offset < newFileSize) {
        addr = (char *)mmap(NULL, (size_t)size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, offset);
        if (addr == MAP_FAILED) {
            handle_error("mmap");
        }

        for (int32_t i = 0; i < size; ++i, ++bytepos) {
            if ((bytepos >= from) && (bytepos < to)) {
                addr[i] = string[l];
                ++l;
            }

            if (bytepos >= to) {
                addr[i] = old[k];
                ++k;
            }
        }

        if (msync(addr, size, MS_SYNC) == -1) {
            handle_error("msync");
        }

        if (munmap(addr, size) == -1) {
            handle_error("munmap");
        }

        offset += size;
    }

    free(old);
}



void replace(const int32_t fd, const int32_t fileSize,  const int32_t RAMLimit, char *oldString,
             const int32_t sizeOldStr, char *newString, const int32_t sizeNewStr)
{
    int32_t size = (RAMLimit > fileSize) ? fileSize : RAMLimit;
    int32_t offset = 0, index = 0, bytepos = 1, from = 0, to = 0;
    char *addr;
    bool found = false;


    while (offset < fileSize) {
        addr = (char *)mmap(NULL, (size_t)size, PROT_READ, MAP_PRIVATE, fd, offset);
        if (addr == MAP_FAILED) {
            handle_error("mmap");
        }

        for (int32_t i = 0; i < size; ++i, ++bytepos) {
            if (addr[i] == oldString[index]) {
                ++index;
                for (int32_t j = i + 1; (index < sizeOldStr) && (j < size); ++index, ++j) {
                    if (oldString[index] != addr[j] || addr[j] == '\n') {
                        index = 0;
                        break;
                    }
                }

                if (index == sizeOldStr) {
                    from = bytepos;
                    found = true;
                    index = 0;
                    break;
                }
            }
        }
        if (munmap(addr, size) == -1) {
            handle_error("munmap");
        }
        offset += size;
    }


    if (!found) {
        printf("This substring no entries in file.\n");
        return;
    }

    int32_t newFileSize = removeOldString(fd, fileSize, RAMLimit, from, from + sizeOldStr);
    insertNewString(fd, newFileSize, RAMLimit, newString, from, from + sizeNewStr);
}