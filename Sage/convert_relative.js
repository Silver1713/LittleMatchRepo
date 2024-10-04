const fs = require('fs');
const path = require('path');

function replaceAllPaths(filePath) {
    let content = fs.readFileSync(filePath, 'utf8');
    const projectDir = path.dirname(filePath);
    const regex = /([a-zA-Z]:\\[^;"'<>\|\n\r]+)/g;

    content = content.replace(regex, (match) => {
        const relativePath = path.relative(projectDir, match);
        return relativePath.replace(/\\/g, '/');
    });

    const outputDirRegex = /<OutputDirectory>([^<]+)<\/OutputDirectory>/g;
    content = content.replace(outputDirRegex, (match, p1) => {
        let outputDir = p1;
        if (!outputDir.endsWith('/')) {
            outputDir += '/';
        }
        console.log(`Output directory: ${outputDir}`);
        return `<OutputDirectory>${outputDir}</OutputDirectory>`;
    });

    fs.writeFileSync(filePath, content, 'utf8');
    console.log('All absolute paths have been replaced with relative paths.');
}

const buildDir = 'build';
const files = fs.readdirSync(buildDir);
const vcxprojOrSlnFiles = files.filter(file => file.endsWith('.vcxproj') || file.endsWith('.sln'));

vcxprojOrSlnFiles.forEach(file => {
    replaceAllPaths(path.join(buildDir, file));
});
