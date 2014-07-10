#define _7SEG_MODE_HEX_VALUE		1
#define _7SEG_MODE_PATTERN		0
#define SEG_MAJOR 			235
#define LCD_IOCTL_MAGIC			SEG_MAJOR
#define LCD_IO(nr)			_IO(LCD_IOCTL_MAGIC,nr)
#define LCD_IOR(nr,size)		_IOR(LCD_IOCTL_MAGIC,nr,size)
#define LCD_IOW(nr,size)		_IOW(LCD_IOCTL_MAGIC,nr,size)
#define LCD_IOWR(nr,size)		_IOWR(LCD_IOCTL_MAGIC,nr,size)

/* ³]©w 7 Segment LED*/
//#define PAUSE		LCD_IOW( 0x72,	10)
#define PAUSE		10
typedef struct _7Seg_Info {			
	unsigned char	Mode ;			/* ³]©w¿é€Jªºžê®ÆŒÒŠ¡ 			*/
	unsigned char	Which ;			/* «ü©wžê®Æ±N³]©wšº­ÓSegment,		*/	 
						/* šÏ¥Îorªº­ÈšÓ«ü©wSegment 		*/
						/* ŠpªG€£¬O¥þ³¡«hžê®Æ 			*/
						/* ³Ì¥kÃäªºSegmentªºžê®ÆŠb³Ì§Cªºbyte    */
						/* or nibble 				*/		
						/* šÒŠp : D5, D8Åã¥Ü58 			*/
						/* Mode  = _7SEG_MODE_HEX_VALUE 	*/
						/* Which = _7SEG_D5_INDEX | _7SEG_D8_INDEX */
						/* Value = 0x58 			*/
						
	unsigned long	Value;			/* ŠUºØModeªº¿é€J­È */
} _7seg_info_t ;
