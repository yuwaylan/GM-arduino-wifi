<!--網頁遊戲設計-->

<html>

<head>
    <meta charset="utf-8">
    <title>img prcress</title>
</head>

<body>
    <center>
        <canvas id="maCanvas" width="600px" height="600px"></canvas><br><br>
        <input id="invert" type="button" value="負片"></input>
        <input id="fadein" type="button" value="淡入"></input>
        <br>
        <input type="range" min="0" max="255" value="255" class="slider" id="RRange">
        <input type="range" min="0" max="255" value="255" class="slider" id="GRange">
        <input type="range" min="0" max="255" value="255" class="slider" id="BRange">
    </center>
    <script>
        var canvas = document.getElementById("maCanvas");
        var ctx = canvas.getContext("2d");
        var image = document.createElement("img");
        var fadestart = false;
        var Rr = document.getElementById("RRange");
        var Gr = document.getElementById("GRange");
        var Br = document.getElementById("BRange");
        image.src = "img.jpg";
        ctx.drawImage(image, 0, 0);
        var btninvert = document.getElementById("invert");
        btninvert.onclick = function() {
            invert();
        }
        Rr.oninput = function() {
            ctx.clearRect(0, 0, canvas.width, canvas.height);
            var pixels = ctx.getImageData(0, 0, image.width, image.height);
            pixels.data[0] = this.value;
            ctx.putImageData(pixels, 0, 0);
            ctx.drawImage(image, 0, 0);
        }

        var btnfadein = document.getElementById("fadein");
        btnfadein.onclick = function() {

            if (!fadestart) {
                /*todo 新增淡入動畫*/
                trans();
            }
            fadestart = !fadestart;
        }

        function trans() {
            for (var i = 0.0; i <= 1.0; i += 0.01) {
                (function(x) {
                    window.setTimeout(function() {
                        ctx.clearRect(0, 0, canvas.width, canvas.height);
                        ctx.globalAlpha = x;
                        ctx.drawImage(image, 0, 0);
                        console.log("trans=" + x);
                    }, 3000 * x);
                })(i);

            }
        }

        function invert() {
            var pixels = ctx.getImageData(0, 0, image.width, image.height);
            for (var i = 0; i < pixels.data.length; i += 4) {
                pixels.data[i] = 255 - pixels.data[i];
                pixels.data[i + 1] = 255 - pixels.data[i + 1];
                pixels.data[i + 2] = 255 - pixels.data[i + 2];
            }
            ctx.putImageData(pixels, 0, 0);
        }
    </script>
</body>

</html>