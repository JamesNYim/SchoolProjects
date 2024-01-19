class Play extends Phaser.Scene {
	constructor() {
	  super("playScene");
	}
	
	create() {
	  const greenColor = 0x00FF00;
	  const whiteColor = 0xFFFFFF;

	  // green UI background
this.add.rectangle(0, 
	borderUISize + borderPadding, 
	game.config.width, borderUISize * 2, 
	greenColor)
	.setOrigin(0, 0)
// white borders
this.add.rectangle(0,
	 0, 
	 game.config.width, 
	 borderUISize, 
	 whiteColor)
	 .setOrigin(0, 0)
this.add.rectangle(0, 
	game.config.height - borderUISize, 
	game.config.width, 
	borderUISize, 
	whiteColor)
	.setOrigin(0, 0)
this.add.rectangle(0, 
	0, 
	borderUISize, 
	game.config.height, 
	whiteColor)
	.setOrigin(0, 0);
this.add.rectangle(game.config.width - borderUISize,
	0, 
	borderUISize, 
	game.config.height, 
	whiteColor)
	.setOrigin(0, 0)
	}
  }