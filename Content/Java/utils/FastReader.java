import java.io.*;
import java.math.*;
import java.util.*;

public class FastReader {
  private final int BUFFER_SIZE = 1 << 16; private int LENGTH = -1;
  private DataInputStream din; private byte[] buffer, buf;
  private int bufferPointer, bytesRead;
  public FastReader(InputStream inputStream) {
    din = new DataInputStream(inputStream); buffer = new byte[BUFFER_SIZE];
    bufferPointer = bytesRead = 0;
  }
  public FastReader(String fileName) throws IOException {
    din = new DataInputStream(new FileInputStream(fileName));
    buffer = new byte[BUFFER_SIZE]; bufferPointer = bytesRead = 0;
  }
  public int nextInt() throws IOException {
    int ret = 0; byte c; do {
      c = read();
    } while (c <= ' ');
    boolean neg = (c == '-'); if (neg) c = read();
    do {
      ret = ret * 10 + c - '0';
    } while ((c = read()) >= '0');
    if (neg) return -ret;
    return ret;
  }
  public long nextLong() throws IOException {
    long ret = 0; byte c; do {
        c = read();
    } while (c <= ' ');
    boolean neg = (c == '-');
    if (neg) c = read();
    do {
        ret = ret * 10 + c - '0';
    } while ((c = read()) >= '0');
    if (neg) return -ret;
    return ret;
  }
  public double nextDouble() throws IOException {
    double ret = 0, div = 1; byte c; do {
      c = read();
    } while (c <= ' ');
    boolean neg = (c == '-');
    if (neg) c = read();
    do {
        ret = ret * 10 + c - '0';
    } while ((c = read()) >= '0');
    if (c == '.') while ((c = read()) >= '0') ret += (c - '0') / (div *= 10);
    if (neg) return -ret;
    return ret;
  }
  public char nextChar() throws IOException {
    byte c; do {
      c = read();
    } while (c <= ' ');
    return (char) c;
  }
  public String next() throws IOException {
    int cnt = 0; byte c; do {
      c = read();
    } while (c <= ' ');
    do {
      buf[cnt++] = c;
    } while ((c = read()) > ' ');
    return new String(buf, 0, cnt);
  }
  public String nextLine() throws IOException {
    while (bufferPointer > 0 && buffer[bufferPointer - 1] == '\r') read();
    int cnt = 0; byte c;
    while ((c = read()) != '\n' && c != '\0') if (c != '\r') buf[cnt++] = c;
    return new String(buf, 0, cnt);
  }
  public void setLength(int len) { LENGTH = len; buf = new byte[len]; }
  public boolean hasNext() throws IOException {
    while (peek() != -1 && peek() <= ' ') read();
    return peek() != -1;
  }
  public boolean hasNextLine() throws IOException {
    while (peek() == '\r') read();
    return peek() != -1;
  }
  private void fillBuffer() throws IOException {
    bytesRead = din.read(buffer, bufferPointer = 0, BUFFER_SIZE);
    if (bytesRead == -1) buffer[0] = -1;
  }
  private byte read() throws IOException {
    if (bufferPointer == bytesRead) fillBuffer();
    return buffer[bufferPointer++];
  }
  private byte peek() throws IOException {
    if (bufferPointer == bytesRead) fillBuffer();
    return buffer[bufferPointer];
  }
  public void close() throws IOException {
    if (din == null) return;
    din.close();
  }
}
