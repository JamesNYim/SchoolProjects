class Main extends Phaser.Scene {
	constructor() {
		super('mainMenuScene');
		console.log('MainMenu: Constructor()');
	}

	init() {
		console.log('MainMenu: init()');
		this.HP = 100;
		this.EXP = 0;
		console.log(`HP: ${this.HP} EXP: ${this.EXP}`);
	}

	create() {
		console.log('MainMenu: create()');
		let playerStats = {
			HP: this.HP,
			EXP: this.EXP
		}
		this.scene.start('playScene', playerStats);
	}
}