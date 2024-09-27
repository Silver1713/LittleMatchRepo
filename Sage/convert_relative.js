const fs = require('fs');
const path = require('path');

// Function to replace all absolute paths with relative paths
function replaceAllPaths(filePath) {
    // Read the file content
    let content = fs.readFileSync(filePath, 'utf8');

    // Get the directory of the file
    const projectDir = path.dirname(filePath);

    // Regular expression to match absolute paths
    const regex = /([a-zA-Z]:\\[^;"'<>\|\n\r]+)/g; // Matches absolute Windows paths (e.g., C:\folder\path)

    // Replace each absolute path with a relative path
    content = content.replace(regex, (match) => {
        const relativePath = path.relative(projectDir, match);
        return relativePath.replace(/\\/g, '/'); // Normalize to forward slashes
    });

    // Write the modified content back to the file
    fs.writeFileSync(filePath, content, 'utf8');
    console.log('All absolute paths have been replaced with relative paths.');
}

// Usage example
// get all file in build folder that is of *.vcxproj or *.sln
const buildDir = 'build';
const files = fs.readdirSync(buildDir);
const vcxprojOrSlnFiles = files.filter(file => file.endsWith('.vcxproj') || file.endsWith('.sln'));


vcxprojOrSlnFiles.forEach(file => {
    replaceAllPaths(path.join(buildDir, file));
});

// replaceAllPaths(vcxprojOrSlnFilePath);
