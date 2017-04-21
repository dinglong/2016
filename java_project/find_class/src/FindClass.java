import java.io.File;
import java.io.FileFilter;
import java.io.IOException;
import java.util.Enumeration;
import java.util.jar.JarEntry;
import java.util.jar.JarFile;

/**
 * 在指定的jar文件，或者指定的路径中的所有jar文件中查找指定的class
 * 
 * @author long
 * 
 */
public class FindClass {
	private final static String EXT = ".jar";

	private String path;
	private String target;
	private int debugLevel = 0;

	public FindClass(String path, String target, String debugLevel) {
		System.out.println("debug level  : " + debugLevel);

		this.path = path;
		this.target = target;
		this.debugLevel = Integer.parseInt(debugLevel);
	}

	public void search() throws IOException {
		File[] files = prepare();

		for (File file : files) {
			String filePath = file.getAbsolutePath();
			JarFile jarFile = new JarFile(file);

			Enumeration<JarEntry> entries = jarFile.entries();

			// 遍历该jar文件中的所有class，包括目录
			while (entries.hasMoreElements()) {
				JarEntry entry = entries.nextElement();

				if (debugLevel > 1) {
					System.out.println("find [" + entry.getName() + "], in jar [" + filePath + "].");
				}

				if (entry.getName().equals(target)) {
					System.out.println("class [" + target + "], in jar [" + filePath + "]");
				}
			}

			jarFile.close();
		}
	}

	private File[] prepare() {
		File file = new File(path);
		File[] files = new File[0];

		if (file.exists()) {
			// 转换成目标格式
			target = target.replace('.', '/') + ".class";

			if (debugLevel > 0) {
				System.out.println("search path  : " + path);
				System.out.println("search target: " + target);
			}

			// 找出要查找的jar文件
			if (file.isFile() && file.getName().endsWith(EXT)) {
				files = new File[] { file };
			} else {
				files = file.listFiles(new ExtFilter(EXT));
			}
		}

		return files;
	}

	/**
	 * 已后缀名过滤文件
	 * 
	 * @author long
	 * 
	 */
	private class ExtFilter implements FileFilter {
		private String ext;

		public ExtFilter(String ext) {
			this.ext = ext;
		}

		@Override
		public boolean accept(File fileName) {
			if (ext != null && fileName.getName().endsWith(ext)) {
				return true;
			}
			return false;
		}

	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		if (args.length < 2) {
			System.out.println("usage: java FindClass <path> <target> [debuglevel(0|1|2)]");
		} else {
			try {
				String debugLevel = "0";

				if (args.length == 3) {
					debugLevel = args[2];
				}

				(new FindClass(args[0], args[1], debugLevel)).search();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
}
