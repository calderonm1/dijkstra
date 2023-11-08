//TODO
/*
-Redo x/y coordinates of vertices for floor 1*
-Upload code to server
*/

//read txt file and store values in temporary div using fetch API
function getCoordinates(callback){
    const fileURL = 'coordinates.txt'; // Name of the input file
    
    fetch(fileURL).then(Response => {
        return Response.text();
    }).then(content => {
        var parsed_coordinates = [];
        var unparsed_coordinates = content.split("\n");

        for (var i = 0; i < unparsed_coordinates.length - 1; ++i){
            //split lines deliminated by comma
            var str_values = unparsed_coordinates[i].split(",");

            //convert str values to int before pushing to arr
            var int_values = str_values.map(function (value) {
                return parseInt(value, 10);
              });
            parsed_coordinates.push(int_values);
        }
        //because fetch is an asynchronous function we must use callback
        callback(parsed_coordinates);
    });
}

//resize the canvas to fit the window it is being viewed
function resizeCanvas(canvasID) {
    var canvas = document.getElementById(canvasID); //Get the canvas element
    var ctx = canvas.getContext("2d"); //Get the 2D rendering context

    //update canvas size
    canvas.width = window.innerWidth;
    canvas.height = window.innerHeight;
}

//draw line onto canvas
function drawLine(canvasID, x1, y1, x2, y2, stroke, width) {
    var canvas = document.getElementById(canvasID); //Get the canvas element
    var ctx = canvas.getContext("2d"); //Get the 2D rendering context

    // start a new path
    ctx.beginPath();

    // place the cursor from the point the line should be started 
    ctx.moveTo(x1 * .67, y1 * .67);

    // draw a line from current cursor position to the provided x,y coordinate
    ctx.lineTo(x2 * .67, y2 * .67);

    // set strokecolor
    ctx.strokeStyle = stroke;

    // set lineWidht 
    ctx.lineWidth = width;

    // add stroke to the line 
    ctx.stroke();
}

//draw path given canvas id
function drawPath(canvasID){
    var canvas = document.getElementById(canvasID); //Get the canvas element
    var ctx = canvas.getContext("2d"); //Get the 2D rendering context
    ctx.clearRect(0, 0, canvas.width, canvas.height); //Clear the canvas

    //generate the coordinates
    getCoordinates(function(parsed_coordinates){
        //iteratively draw lines
        var i = 0;
        while (i < parsed_coordinates.length - 1){
            var start = parsed_coordinates[i];
            var end = parsed_coordinates[i + 1];
            drawLine(canvasID, start[0], start[1], end[0], end[1], '#6495ED', 10);
            ++i;
        }
    });
}