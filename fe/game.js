function setup() {
	var canvas = document.getElementById('circle');
	if(canvas.getContext) {
		canvas.width = 800;
		canvas.height = 600;
		var ctx = canvas.getContext('2d');
		var X = 0;
		var Y = 0;
		var R = 45;
		ctx.beginPath();
		ctx.arc(X, Y, R, 0, 2*Math.PI, false);
		ctx.lineWidth = 3;
		ctx.strokeStyle = '#FF0000';
		ctx.stroke();
	}
}
