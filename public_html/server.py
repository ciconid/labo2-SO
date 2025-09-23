from http.server import SimpleHTTPRequestHandler, HTTPServer
import os, json

class MiHandler(SimpleHTTPRequestHandler):
    def do_GET(self):
        if self.path == "/archivos":
            # Listar todos los .txt del directorio actual
            txts = [f for f in os.listdir(".") if f.endswith(".txt")]
            self.send_response(200)
            self.send_header("Content-type", "application/json")
            self.end_headers()
            self.wfile.write(json.dumps(txts).encode("utf-8"))
        else:
            super().do_GET()

if __name__ == "__main__":
    server = HTTPServer(("localhost", 8000), MiHandler)
    print("Servidor corriendo en http://localhost:8000")
    #server.serve_forever()
    try:
        server.serve_forever()
    except KeyboardInterrupt:
        print("\nServer stopped.")
        server.shutdown()
