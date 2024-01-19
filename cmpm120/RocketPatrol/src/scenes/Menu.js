class Menu extends Phaser.Scene {
	constructor() {
	  super("menuScene");
	}
	
	preload() {
		this.load.image('rocket', './assets/rocket.png');
		this.load.image('spaceship', './assets/spaceship.png');
		this.load.image('starfield', './assets/starfield.png');
		// load spritesheet
		this.load.spritesheet('explosion', './assets/explosion.png', {
			frameWidth: 64,
			frameHeight: 32,
			startFrame: 0,
			endFrame: 9
		})
	}
	create() {
	// animation configuration
	this.anims.create({
		key: 'explode',
		frames: this.anims.generateFrameNumbers('explosion', { start: 0, end: 9, first: 0}),
		frameRate: 30
	})

	  this.add.text(20, 20, "Rocket Patrol Menu");
	  this.scene.start("playScene");
	}
  }