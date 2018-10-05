var rect = function(ctx, x, y, w, h, desc) {
  x = Math.floor(x) + 0.5;
  y = Math.floor(y) + 0.5;
  w = Math.ceil(w);
  h = Math.ceil(h);
  ctx.lineWidth = 1;
  ctx.strokeRect(x, y, w, h);
  if (desc) {
    ctx.font = '12px monospace';
    ctx.fillText(desc, x, y - 5);
  }
};

var hline = function(ctx, y, desc, size) {
  y = Math.ceil(y) + 0.5;
  ctx.lineWidth = 1;
  ctx.beginPath();
  ctx.moveTo(0, y);
  ctx.lineTo(size, y);
  ctx.stroke();
  if (desc) {
    ctx.font = '12px monospace';
    ctx.fillText(desc, 0, y - 5);
  }
};

var vm = new Vue({
  el: '#app',
  data: {
    fontname: '',
    font: null,
    text: 'hello, world!',
    advance_width: 0,
    mouse_down: false,
    options: {
      glyph_size: 0,
      canvas_width: 0,
      canvas_height: 0,
      origin_x: 0,
      origin_y: 0,
      origin: true,
      baseline: true,
      points: false,
      box: false,
      kerning: true,
      hinting: false
    }
  },
  methods: {
    onFontLoaded: function(font) {
      this.font = font;
      this.renderText();
    },
    setCanvasSize: function() {
      var canvas = document.getElementById('canvas');
      canvas.style.display='none';
      var canvas_div = document.getElementById('canvas-div');
      var w = ((canvas_div.clientWidth - 10) & 0xfffc) * window.devicePixelRatio;
      var h = ((canvas_div.clientHeight - 10) & 0xfffc) * window.devicePixelRatio;
      canvas.style.display='block';

      if (w !== this.options.canvas_width) {
        this.options.canvas_width = w;
        canvas.width = w;
        canvas.style.width = w / window.devicePixelRatio + 'px';
      }
      if (h !== this.options.canvas_height) {
        this.options.canvas_height = h;
        canvas.height = h;
        canvas.style.height = h / window.devicePixelRatio + 'px';
      }
    },
    renderText: function() {
      if (!this.font) {
        return;
      }

      var canvas = document.getElementById('canvas');
      var ctx = canvas.getContext('2d');
      ctx.clearRect(0, 0, this.options.canvas_width, this.options.canvas_height);

      if (this.options.baseline) {
        // draw baseline, ascender, descender
        ctx.strokeStyle = '#aaa';
        ctx.fillStyle = '#aaa';
        hline(ctx, this.options.origin_y, 'baseline', this.options.canvas_width);
        hline(ctx, this.options.origin_y - this.font.tables.hhea.ascender * this.pixels_per_unit, 'hhea ascender', this.options.canvas_width);
        hline(ctx, this.options.origin_y - this.font.tables.hhea.descender * this.pixels_per_unit, 'hhea descender', this.options.canvas_width);
      }

      if (!this.text) {
        return;
      }

      var options = {
        kerning: this.options.kerning,
        hinting: this.options.hinting
      };

      var paths = this.font.getPaths(this.text, this.options.origin_x, this.options.origin_y, this.options.glyph_size, options);

      this.advance_width = this.font.getAdvanceWidth(this.text, this.options.glyph_size, options);

      if (this.options.origin_x === 0 && this.options.origin_y === 0) {
        this.resetOrigin();
      }

      //this.font.draw(ctx, this.text, this.options.origin_x, this.options.origin_y, this.options.glyph_size, options);
      for (let i = 0; i < paths.length; i++) {
        paths[i].draw(ctx);
      }

      if (this.options.points) {
        this.font.drawPoints(ctx, this.text, this.options.origin_x, this.options.origin_y, this.options.glyph_size, options);
      }
      if (this.options.box) {
        ctx.strokeStyle = 'blue';
        for (let i = 0; i < paths.length; i++) {
          var box = paths[i].getBoundingBox();
          if (box.x1 !== box.x2 && box.y1 !== box.y2) {
            rect(ctx, box.x1, box.y1, box.x2 - box.x1, box.y2 - box.y1);
          }
        }
      }

      if (this.options.origin) {
        // draw origin
        ctx.fillStyle = '#333';
        ctx.beginPath();
        ctx.arc(this.options.origin_x, this.options.origin_y, 3, 0, Math.PI * 2);
        ctx.fill();
        ctx.fillText('origin', this.options.origin_x - 50, this.options.origin_y - 5);

        // draw advance width
        ctx.fillStyle = '#aaa';
        ctx.beginPath();
        ctx.arc(this.options.origin_x + this.advance_width, this.options.origin_y, 3, 0, Math.PI * 2);
        ctx.fill();
        ctx.fillText('advance width', this.options.origin_x + this.advance_width, this.options.origin_y - 5);
      }
    },
    resetOrigin: function() {
      this.options.origin_x = Math.floor((this.options.canvas_width - this.advance_width) / 2);
      this.options.origin_y = Math.floor(this.options.canvas_height * 4 / 5 + this.font.tables.os2.sTypoDescender * this.pixels_per_unit);
    },
    resetGlyphSize: function() {
      var glyph_size;
      if (this.options.canvas_height < this.options.canvas_width) {
        glyph_size = this.options.canvas_height * 4 / 5;
      } else {
        glyph_size = this.options.canvas_width * 4 / 5;
      }
      if (this.text && this.text.length > 1) {
        glyph_size /= this.text.length;
      }
      this.options.glyph_size = Math.floor(glyph_size);
    },
    resizeGlyph: function(evt) {
      var delta = 0;
      if (evt.wheelDelta) {
        delta = -evt.wheelDelta / 120;
      }
      if(evt.deltaY) {
        evt.deltaY > 0 ? delta = 1 : delta = -1;
      }
      this.options.glyph_size = this.options.glyph_size - delta * 5;
    },
    mousemove: function(evt) {
      if (this.mouse_down) {
        var x = evt.clientX - this.mouse_x;
        var y = evt.clientY - this.mouse_y;
        this.mouse_x = evt.clientX;
        this.mouse_y = evt.clientY;
        this.options.origin_x += x * window.devicePixelRatio;
        this.options.origin_y += y * window.devicePixelRatio;
      }
    },
    mousedown: function(evt) {
      this.mouse_x = evt.clientX;
      this.mouse_y = evt.clientY;
      this.mouse_down = true;
    },
    mouseup: function(evt) {
      this.mouse_down = false;
    },
    openfile: function(evt) {
      var file = evt.target.files[0];
      this.fontname = file.name;
      var that = this;
      var reader = new FileReader();
      reader.onload = function(e) {
        try {
          that.font = opentype.parse(e.target.result);
          that.onFontLoaded(that.font);
        } catch (err) {
          console.error(err);
        }
      };
      reader.onerror = function(err) {
        console.log(err);
      };
      reader.readAsArrayBuffer(file);
    }
  },
  created: function() {
    window.addEventListener('resize', this.setCanvasSize);
    this.fontname = 'DejaVuSansMono.ttf';
  },
  mounted: function() {
    this.setCanvasSize();
    this.resetGlyphSize();
  },
  computed: {
    pixels_per_unit: function() {
      return this.options.glyph_size / this.font.unitsPerEm;
    }
  },
  watch: {
    fontname: function(name) {
      this.font = null;
      var that = this;
      opentype.load('font/' + name, function(err, font) {
        if (err) {
          console.error(err.toString());
          return;
        }
        that.onFontLoaded(font);
      });
    },
    text: function() {
      this.renderText();
    },
    options: {
      handler: function() {
        this.renderText();
      },
      deep: true
    }
  }
});
